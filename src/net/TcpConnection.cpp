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
      if(n>0)
      {
         outputBuffer_.retrieve(n);
         if(!outputBuffer_.readbyte())
         channel_->disableWriting();
         if(writeCompleteCallback_)
         {
            loop_->queueInLoop(std::bind(writeCompleteCallback_,shared_from_this()));
         }
      }
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
}
// Eventloop *loop_;
// const std::string name_;
// State state_; // FIXME: use atomic variable
// bool reading_;
// // we don't expose those classes to client.
// std::unique_ptr<Socket> socket_;
// std::unique_ptr<Channel> channel_;
// const InetAddress localAddr_;
// const InetAddress peerAddr_;
// ConnectionCallback connectionCallback_;
// MessageCallback messageCallback_;
// WriteCompleteCallback writeCompleteCallback_;
// CloseCallback closeCallback_;
// size_t highWaterMark_;
// netbuffer inputBuffer_;
// netbuffer outputBuffer_;