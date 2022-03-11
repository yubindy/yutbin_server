#include "Acceptor.hpp"
#include <fcntl.h>
using namespace yb;
using namespace yb::net;
// Eventloop *loop;
// Socket acceptsocket;
// Channel acceptChannel;
// NewConnectionback NewConnection_;
// bool listen_;
// int fd_;
Acceptor::Acceptor(Eventloop *loop_, const InetAddress &listenaddr, bool reuseport) : loop(loop_), acceptsocket(createNonblockingOrDie(listenaddr.family())),
                                                                                      acceptChannel(loop, acceptsocket.fd()), fd_(open("/dev/null", O_RDONLY | O_CLOEXEC))
{
    assert(fd_ >= 0);
    acceptsocket.setReuseAddr(true);
    acceptsocket.setReusePort(true);
    acceptsocket.bindAddress(listenaddr);
    acceptChannel.setreadback(std::bind(&Acceptor::handleRead, this));
}
Acceptor::~Acceptor()
{
    acceptChannel.disableAll();
    acceptChannel.remove();
    close(fd_);
}
void Acceptor::listen()
{
    loop->assertInLoopThread();
    listen_ = true;
    acceptsocket.listen();
    acceptChannel.enableReading();
}
void Acceptor::handleRead() // channel 回调
{
    loop->assertInLoopThread();
    InetAddress peerAddr;
    int connfd = acceptsocket.accept(&peerAddr);
    if (connfd >= 0)
    {
        std::string hostport = peerAddr.toIpPort();
        LOG(lev::DEBUG) << "open connfd: " << connfd << "accept from " << hostport << endl;
        if (NewConnection_)
            NewConnection_(connfd, peerAddr);
        else
            close(connfd);
    }
    else //文件描述符不足
    {
        if (errno == EMFILE)
        {
            close(fd_);
            fd_ = net::accept(acceptsocket.fd(), NULL);
            close(fd_);
            fd_ = open("/dev/null", O_RDONLY | O_CLOEXEC);
        }
        else
        {
            LOG(lev::ERROR) << "Acceptor::handleRead accept error" << endl;
        }
    }
}
