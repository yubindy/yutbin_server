#include "Tcpserver.hpp"
#include "Eventloop.hpp"
using namespace yb;
using namespace yb::net;
Tcpserver::Tcpserver(Eventloop *loop, const InetAddress address, const std::string &name_, int numthread = 4) : main(loop), ip(address.toIpPort()), port(address.toPort()),
                                                                                                                acceptor_(new Acceptor(loop, address, true)), threadpool_(new EventloopThreadpool(mainloop)) connback(defaultConnectionCallback), messback(defaultMessageCallback)
{
    acceptor_->setConnectionback(std::bind(&Tcpserver::newConnection, this, _1, _2));
    threadPool_->setThreadNum(numthread);
}
Tcpserver::~Tcpserver()
{
    mainloop->assertInLoopThread();
    nextConnId_ = 1;
    LOG(lev::INFO) << "yutbin server " << name << "quit" << endl;
    fprintf(stdout, "yutbin server %s quit", name);
    for (Connectmap::iterator &it : connects)
    {
        Tcpconnection conn(it.second);
        it.second.reset();
        conn->getloop()->runInLoop(std::bind(&Tcpconnection::connectDestroyed, conn));
    }
}
void Tcpserver::setThreadnums(int num)
{
    assert(num >= 0);
    threadPool_->setThreadNum(num);
}
void Tcpserver::start()
{
    if (stared_.compare_exchange_strong(false, true) == 0)
    {
        threadpool_->start(ThreadInitback);
        loop_->runinloop(std::bind(&Acceptor::listen, get_pointer(acceptor_)));
    }
}
void Tcpserver::newConnection(int sockfd, const InetAddress &addr) // accept 回调
{
    mainloop->assertInLoopThread();
    Eventloop *ioloop = threadloop_->getNextloop();
    char buf[64];
    snprintf(buf, sizeof(buf), "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;
    std::string connName = name + buf;
    LOG(lev::INFO) << "TcpServer::newConnection [" << name
                   << "] - new connection [" << connName
                   << "] from " << addr.toIpPort() << endl;
    InetAddress peerAddr(getLocalAddr(sockfd)); //获取本地地址
    Tcpconptr conn(new TcpConnection(mainloop, sockfd, connName, addr, peerAddr));
    connects[connName] = connName;
    conn->setConnectionback(connback);
    conn->setMessageCallback(messback);
    conn->setWriteCompleteCallback(writeback);
    conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, _1));
    ioloop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}
void TcpServer::removeConnection(const TcpConnectionPtr &conn)
{
    Eventloop *subloop = conn->getloop();
    
}
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
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