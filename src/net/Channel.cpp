#include "Channel.hpp"
#include "poller.hpp"
#include<sstream>
using namespace yb;
using namespace yb::net;
static const int kNoneEvent = EPOLLET;
static const int kReadEvent = EPOLLIN | EPOLLRDHUP | EPOLLPRI;
static const int kWriteEvent = EPOLLOUT;
Channel::Channel(Eventloop *loop_, int fd_) : loop(loop_), recvevents_(kNoneEvent), fd(fd_), status(kNew), tied_(false) {}
Channel::~Channel() {}
void Channel::update()
{

    loop->updateChannel(this);
}
void Channel::remove()
{

    loop->removeChannel(this);
}

void Channel::tie(const std::shared_ptr<void> &pt)
{
    tie_ = pt;
    tied_ = true;
}

void Channel::handleEvent(Timestamp recvtime)
{
    std::shared_ptr<void> pt;
    if (tied_)
    {
        pt = tie_.lock();
        if (pt)
        {
            handleEVentwithguard(recvtime);
        }
    }
    else
    {
        handleEVentwithguard(recvtime);
    }
}
void Channel::handleEVentwithguard(Timestamp recvtime)
{
    LOG(lev::TRACE) << reventsToString();
    if ((recvevents_ & EPOLLHUP) && !(recvevents_ & EPOLLIN))
    {
        // if (logHup_)
        // {
        //   LOG(lev::WARN) << "fd = " << fd_ << " Channel::handle_event() POLLHUP";
        // }
        if (closeCallback_)
            closeCallback_();
    }

    if (recvevents_ & POLLNVAL)
    {
        LOG(lev::WARN) << "fd = " << fd << " Channel::handle_event() POLLNVAL";
    }

    if (recvevents_ & (EPOLLERR | POLLNVAL))
    {
        if (errorCallback_)
            errorCallback_();
    }
    if (recvevents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        if (readCallback_)
            readCallback_();
    }
    if (recvevents_ & EPOLLOUT)
    {
        if (writeCallback_)
            writeCallback_();
    }
}
std::string Channel::reventsToString()
{
    std::ostringstream os;
    os << fd << ":";
    if (events_ & EPOLLIN)
        os << "IN ";
    if (events_ & EPOLLPRI)
        os << "PRI ";
    if (events_ & EPOLLOUT)
        os << "OUT ";
    if (events_ & EPOLLHUP)
        os << "HUP ";
    if (events_ & EPOLLRDHUP)
        os << "RDHUP ";
    if (events_ & EPOLLERR)
        os << "ERR ";
    if (events_ & POLLNVAL)
        os << "NVAL ";
    return os.str();
}
