#include "Tcpclient.hpp"
using namespace yb;
using namespace yb::net;
TcpClient::TcpClient(Eventloop *loop,
                     const InetAddress &serverAddr,
                     const std::string &nameArg)
    : loop_(loop),
      connector_(new Connector(loop, serverAddr)),
      name_(nameArg),
      connectionCallback_(defaultConnectionCallback),
      messageCallback_(defaultMessageCallback),
      retry_(false), //失败时是否重连
      connect_(true),
      nextConnId_(1)
{
    connector_->setNewConnectionCallback(
        std::bind(&TcpClient::newConnection, this, _1)); //给connector设置连接成功时的回调
}
void TcpClient::newConnection(int sockfd)
{
    loop_->assertInLoopThread();
    InetAddress peerAddr(getPeerAddr(sockfd));
    char buf[32];
    snprintf(buf, sizeof buf, ":%s#%d", peerAddr.toIpPort().c_str(), nextConnId_);
    ++nextConnId_; //对连接进行计数
    std::string connName = name_ + buf;

    InetAddress localAddr(getLocalAddr(sockfd));

    TcpConnectionPtr conn(new TcpConnection(loop_,
                                            sockfd,
                                            connName,
                                            localAddr,
                                            peerAddr));

    conn->setConnectionCallback(connectionCallback_);       
    conn->setMessageCallback(messageCallback_);             
    conn->setWriteCompleteCallback(writeCompleteCallback_); 
    conn->setCloseCallback(
        std::bind(&TcpClient::removeConnection,this, _1)); 
    {
        std::lock_guard<std::mutex> lock(mutex_);
        connection_=conn; //每个Tcpclient对应一个TcpConnection
    }
    conn->connectEstablished(); //加入IO multiplexing //注册可读事件
}
void TcpClient::removeConnection(const TcpConnectionPtr &conn)
{
    loop_->assertInLoopThread();
    assert(loop_ == conn->getLoop());
    {
        std::lock_guard<std::mutex> lock(mutex_);
        connection_.reset();
    }
    loop_->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
    if (retry_ && connect_)
    {
        LOG(lev::INFO) << "TcpClient::connect[" << name_ << "] - Reconnecting to "
                       << connector_->serverAddress().toIpPort();
        connector_->restart();
    }
}