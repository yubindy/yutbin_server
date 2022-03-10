#include "TcpConnection.hpp"
using namespace yb;
using namespace yb::net;
void TcpConnection::defaultConnectionCallback(const TcpConnectionPtr &conn)
{
   LOG(lev::TRACE) << conn->localAddress().toIpPort() << " -> "
                   << conn->peerAddress().toIpPort() << " is "
                   << (conn->connected() ? "UP" : "DOWN");
}
void TcpConnection::defaultMessageCallback(const TcpConnectionPtr &conn, netbuffer *buf)
{
   buf->retrieveAll();
}
TcpConnection::TcpConnection(Eventloop *loop, int sockfd, const std::string &nameArg,
                             const InetAddress &localAddr, const InetAddress &peerAddr) : loop_(loop), name_(nameArg), state_(kConnecting), socket_(new Socket(sockfd)),
                                                                                          channel_(new Channel(loop, sockfd)), localAddr_(localAddr), peerAddr_(peerAddr), highWaterMark_(64 * 1024 * 1024)
{
   channel_->setreadback(std::bind(&TcpConnection::handleRead, this, _1));
   channel_->serwriteback(std::bind(&TcpConnection::handleWrite, this));
   channel_->setcloseback(std::bind(&TcpConnection::handleClose, this));
   channel_->seterrorback(std::bind(&TcpConnection::handleError, this));
   LOG(lev::DEBUG) << "TcpConnection::ctor[" << name_ << "] at " << this
                   << " fd=" << sockfd;
   socket_->setKeepAlive(true);
}
void TcpConnection::handleRead(Timestamp receiveTime)
{
   loop_->assertInLoopThread();
   int saveerror = 0;
   size_t n = inputBuffer_.readfd(channel_->getfd(), &saveerror);
   if (n > 0)
   {
      messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
   }
   else if (n == 0)
   {
      handleClose();
   }
   else
   {
      errno = saveerror;
      LOG(lev::ERROR) << "TcpConnection::handleRead";
      handleError();
   }
}
void TcpConnection::handleWrite()
{
   loop_->assertInLoopThread();
   if (channel_->isWriting())
   {
      ssize_t n = write(channel_->getfd(), outputBuffer_.peek(),
                        outputBuffer_.readbyte());
      if (n > 0)
      {
         outputBuffer_.retrieve(n);
         if (!outputBuffer_.readbyte())
            channel_->disableWriting();
         if (writeCompleteCallback_)
         {
            loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
         }
         if (state_ == kDisconnecting)
         {
            shutdownInLoop();
         }
      }
      else
      {
         LOG(lev::ERROR) << "TcpConnection::handleWrite";
      }
   }
   else
   {
      LOG(lev::TRACE) << "Connection fd = " << channel_->getfd()
                      << " is down, no more writing";
   }
}
void TcpConnection::handleClose()
{
   loop_->assertInLoopThread();
   assert(state_ == kConnected || state_ == kDisconnecting);
   setState(kDisconnected);
   channel_->disableAll();
}
void TcpConnection::handleError()
{
   int err = getSocketError(channel_->getfd());
   LOG(lev::ERROR) << "TcpConnection::handleError [" << name_
                   << "] - SO_ERROR = " << err << " " << strerror_mr(err);
}
void TcpConnection::send(const void *message, int len)
{
   if (state_ == kConnected)
   {
      Eventloop *subloop = getLoop();
      if (subloop->isInLoopThread())
      {
         sendInLoop(message, len);
      }
      else
      {
         subloop->runInLoop(
             [this, message, len]()
             { this->sendInLoop(message, len); });
      }
   }
}
void TcpConnection::send(std::string &message)
{
   if (state_ == kConnected)
   {
      if (loop_->isInLoopThread())
      {
         sendInLoop(message);
      }
      else
      {
         //  loop_->runInLoop(std::bind(&TcpConnection::sendInLoop,this,message));
         loop_->runInLoop([this, message]
                          { this->sendInLoop(message);});   
      }
   }
}

void TcpConnection::sendInLoop(std::string &message)
{
   sendInLoop(static_cast<const void *>(message.c_str()),
              message.size());
}
void TcpConnection::sendInLoop(const void *message, size_t len)
{
   loop_->assertInLoopThread();
   ssize_t nwrite = 0;
   size_t remaining = len;
   bool err = false;
   if (state_ == kDisconnected)
   {
      LOG(lev::WARN) << "disconnected, give up writing";
      return;
   }
   if (!channel_->isWriting() && outputBuffer_.readbyte() == 0)
   {
      nwrite = ::write(channel_->getfd(), message, len);
      if (nwrite > 0)
      {
         remaining = len - nwrite;
         if (remaining == 0 && writeCompleteCallback_)
         {
            loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
         }
      }
   }
   else
   {
      nwrite = 0;
      if (errno != EWOULDBLOCK)
      {
         if (errno == EPIPE || errno == ECONNRESET) // FIXME: any others?
         {                                          //服务端收到RST报文后 write出现EPIPE recv出现ECONNRESET
            err = true;                             //出现错误
         }
      }
   }
   assert(remaining <= len);
   if (!err && remaining > 0)
   {
      outputBuffer_.append(static_cast<const char *>(message) + nwrite, remaining);
      if (!channel_->isWriting())
      {
         channel_->enableWriting();
      }
   }
}
void TcpConnection::shutdown()
{
   // FIXME: use compare and swap
   if (state_ == kConnected)
   {
      setState(kDisconnecting);
      // FIXME: shared_from_this()?
      loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
   }
}
void TcpConnection::shutdownInLoop()
{
   loop_->assertInLoopThread();
   if (!channel_->isWriting())
   {
      // we are not writing
      socket_->shutdownWrite();
   }
}
void TcpConnection::forceClose()
{
   if (state_ == kConnected || state_ == kDisconnecting)
   {
      setState(kDisconnecting);
      loop_->queueInLoop(std::bind(&TcpConnection::forceCloseInLoop, shared_from_this()));
   }
}
void TcpConnection::forceCloseInLoop()
{
   loop_->assertInLoopThread();
   if (state_ == kConnected || state_ == kDisconnecting)
   {

      handleClose();
   }
}
void TcpConnection::setTcpNoDelay(bool on)
{
   socket_->setTcpNoDelay(on);
}

void TcpConnection::startRead()
{
   loop_->runInLoop(std::bind(&TcpConnection::startReadInLoop, this));
}
void TcpConnection::startReadInLoop()
{
   loop_->assertInLoopThread();
   if (!reading_ || channel_->isReading())
   {
      channel_->enableReading();
      reading_ = true;
   }
}
void TcpConnection::stopRead()
{
   loop_->runInLoop(std::bind(&TcpConnection::stopReadInLoop, this));
}
void TcpConnection::stopReadInLoop()
{
   loop_->assertInLoopThread();
   if (reading_ || channel_->isReading())
   {
      channel_->disableReading();
      reading_ = false;
   }
}
void TcpConnection::connectEstablished()
{
   loop_->assertInLoopThread();
   assert(state_ == kConnecting);
   setState(kConnected);
   channel_->tie(shared_from_this());
   channel_->enableReading();
   connectionCallback_(shared_from_this());
}
void TcpConnection::connectDestroyed()
{
   loop_->assertInLoopThread();
   if (state_ == kConnected)
   {
      setState(kDisconnected);
      channel_->disableAll();
      connectionCallback_(shared_from_this());
   }
   channel_->remove();
}
