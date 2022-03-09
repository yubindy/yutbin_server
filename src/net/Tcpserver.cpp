#include "Tcpserver.hpp"
#include "Eventloop.hpp"
using namespace yb;
using namespace yb::net;
Tcpserver::Tcpserver(Eventloop *loop, const InetAddress address, const std::string &name,int numthread) : mainloop(loop), ipport(address.toIpPort()),
                                                                                                          acceptor_(new Acceptor(loop, address, true)), threadpool_(new EventloopThreadpool(mainloop)),
                                                                                                          connback(defaultConnectionCallback), messback(defaultMessageCallback),threadnum(numthread)
{
    acceptor_->setConnectback(std::bind(&Tcpserver::newConnection, this, _1, _2));
    threadpool_->setThreadNum(numthread);
}
Tcpserver::~Tcpserver()
{
    mainloop->assertInLoopThread();
    nextConnId_ = 1;
    LOG(lev::INFO) << "yutbin server " << name << "quit" << endl;
    fprintf(stdout, "yutbin server %s quit", name.data());
    for (auto &it : connects)
    {
        TcpConnectionPtr conn(it.second);
        it.second.reset();
        conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
    }
}
void Tcpserver::setThreadnums(int num)
{
    assert(num >= 0);
    threadpool_->setThreadNum(num);
}
void Tcpserver::start()
{    
    bool expect=false;
    if (stared_.compare_exchange_strong(expect,true))
    {
        threadpool_->start(threadinit_);//启动i/o线程池
        mainloop->runInLoop(std::bind(&Acceptor::listen,acceptor_));
    }
}
void Tcpserver::newConnection(int sockfd, const InetAddress &peerAddr) // accept 回调
{
    mainloop->assertInLoopThread();
    Eventloop *ioloop = threadpool_->getNextLoop(); 
    char buf[64];
    snprintf(buf, sizeof(buf), "-%s#%d", ipport.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name + buf;
    LOG(lev::INFO) << "TcpServer::newConnection [" << name
                   << "] - new connection [" << connName
                   << "] from " << peerAddr.toIpPort() << endl;
    InetAddress localAddr(getLocalAddr(sockfd)); //获取本地地址
    Tcpconptr conn(new TcpConnection(ioloop,sockfd,connName,localAddr,peerAddr));
    connects[connName] = conn;
    conn->setConnectionCallback(connback);
    conn->setMessageCallback(messback);
    conn->setWriteCompleteCallback(writeback);
    conn->setCloseCallback(std::bind(&Tcpserver::removeConnection, this, _1));
    ioloop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}
void Tcpserver::removeConnection(const TcpConnectionPtr &conn)
{
   mainloop->runInLoop(std::bind(&Tcpserver::removeConnectionInLoop,this,conn));
}
void Tcpserver::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
    mainloop->assertInLoopThread();
    size_t n=connects.erase(conn->name());
    assert(n==1);
    Eventloop* ioloop=conn->getLoop();
    ioloop->queueInLoop(std::bind(&TcpConnection::connectDestroyed,conn));
}
// std::shared_ptr<Eventloop> mainloop;
// const std::string ipport;
// const std::string name;
// std::unique_ptr<Acceptor> acceptor_;
// std::shared_ptr<EventloopThreadpool> threadpool_;
// ConnectionCallback connback;
// MessageCallback messback;
// WriteCompleteCallback writeback;
// ThreadInitback threadinit_;
// Connectmap connects;
// std::atomic<bool> stared_;
// int threadnum;