#include "Connector.hpp"
using namespace yb;
using namespace yb::net;
Connector::Connector(Eventloop *loop, const InetAddress &serverAddr)
    : loop_(loop),                     //本线程事件循环
      serverAddr_(serverAddr),         //要连接的服务端地址
      connect_(false),                 //是否开始连接 start中触发
      state_(kDisconnected)          //设置连接状态
{
    LOG(lev::DEBUG) << "ctor[" << this << "]"<<endl;
}
void Connector::Start()
{
    connect_ = true;
    loop_->runInLoop(std::bind(&Connector::startInLoop, this));
}
void Connector::startInLoop()
{
    loop_->assertInLoopThread();
    assert(state_ == kConnected);
    if (connect_)
    {
        connect();
    }
    else
    {
        LOG(lev::DEBUG) << "do not connect";
    }
}
void Connector::connect()
{
    int sockfd = createNonblockingOrDie(serverAddr_.family());
    int ret = net::connect(sockfd, serverAddr_.getSockAddr());
    int err = (ret == 0) ? 0 : errno;
    switch (err)
    {
    case 0:
    case EINPROGRESS:
    case EINTR:
    case EISCONN:
        connecting(sockfd);
        break;
    case EAGAIN:        //临时端口(ephemeral port)不足
    case EADDRINUSE:    //监听的端口已经被使用
    case EADDRNOTAVAIL: //配置的IP不对
    case ECONNREFUSED:  //服务端在我们指定的端口没有进程等待与之连接
    case ENETUNREACH:   //表示目标主机不可达
        retry(sockfd);  //重连接
        break;

    case EACCES:       //没有权限
    case EPERM:        //操作不被允许
    case EAFNOSUPPORT: //该系统不支持IPV6
    case EALREADY:     //套接字非阻塞且进程已有待处理的连接
    case EBADF:        //无效的文件描述符
    case EFAULT:       //操作套接字时的一些参数无效
    case ENOTSOCK:     //不是一个套接字
        LOG(lev::ERROR) << "connect error in Connector::startInLoop " << err;
        close(sockfd);
        break;

    default:
        LOG(lev::ERROR) << "Unexpected error in Connector::startInLoop " << err;
        close(sockfd);
        break;
    }
}
void Connector::connecting(int sockfd)
{
    setState(kConnecting);
    assert(!channel_);
    channel_.reset(new Channel(loop_, sockfd));
    channel_->serwriteback(std::bind(&Connector::handleWrite, this));
    channel_->seterrorback(std::bind(&Connector::handleError, this));
    channel_->enableWriting();
}
void Connector::handleWrite()
{
    if (state_ == kConnecting)
    {
        int sockfd = removeAndResetChannel();      //从poller中移除,并把channel置为空 socket出错无法恢复
        int err =getSocketError(sockfd); 
        if (err)
        {
            LOG(lev::WARN) << "Connector::handleWrite - SO_ERROR = "
                     << err << " " << strerror_mr(err)<<endl;
            retry(sockfd); 
        }
        else
        {
            setState(kConnected);
            if (connect_)
            {
                newConnectionCallback_(sockfd); // 在TCPClient中设置
            }
            else
            {
               close(sockfd);
            }
        }
    }
    else
    {
        // what happened?
        assert(state_ == kDisconnected);
    }
}
void Connector::handleError()
{
    LOG(lev::ERROR)<< "Connector::handleError state=" << state_;
    if(state_==kConnecting)
    {
        int sockfd=removeAndResetChannel();
        int err=getSocketError(sockfd);
        retry(sockfd);
    }
}
void Connector::retry(int sockfd)
{
    close(sockfd);
    setState(kDisconnected); //设置状态为未连接
  if (connect_) //执行了start后执行这个
  {
    LOG(lev::INFO) << "Connector::retry - Retry connecting to " << serverAddr_.toIpPort()<<"now unstart"<<endl;
    loop_->runInLoop(std::bind(&Connector::startInLoop, shared_from_this())); //设置一个定时事件
  }
  else
  {
    LOG(lev::DEBUG) << "do not connect\n";
  }
}