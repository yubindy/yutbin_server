#include "poller.hpp"
#include<cassert>
using namespace yb;
using namespace yb::net;

poller::poller(Eventloop *loop_) : epfd(epoll_create1(EPOLL_CLOEXEC)), loop(loop_), list(36)
{
    if (epfd < 0)
    {
        LOG(lev::ERROR) << "poller:epoll_create1" << endl;
    }
}
Timestamp poller::poll(int timeoutMs, channelist *activeChannels)
{
    int num = epoll_wait(epfd, &*list.begin(), static_cast<int>(list.size()), timeoutMs);
    int saveerr = errno;
    Timestamp now(Timestamp::now());
    if (num > 0)
    {
        LOG(lev::TRACE) << num << " events happened" << endl;
        fillActiveChannels(num,activeChannels);
        if(num==list.size())
        {
            list.resize(num*2);
        }
    }
    else if (num == 0)
    {
        LOG(lev::TRACE) << "nothing happened" << endl;
    }
    else if (num < 0)
    {
        LOG(lev::ERROR) << endl;
    }
    return now;
}
void poller::updatechannel(Channel *channel_)
{
    poller::assertinloop();
    int status = channel_->getstatus();
    int fd = channel_->getfd();
    if (status == kNew || status == kDeleted)
    {
        if (status == kNew)
        {
            assert(channels.find(fd) == channels.end());
            channels[fd] = channel_;
        }
        else
        {
            assert(channels.find(fd) != channels.end());
        }
        channel_->setstatus(KAdded);
        update(EPOLL_CTL_ADD, channel_);
    }
    else
    {
        assert(channels[fd] == channel_);
        if (channel_->isNoneEvent())
        {
            channel_->setstatus(kDeleted);
            update(EPOLL_CTL_DEL, channel_);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel_);
        }
    }
    return;
}
void poller::removechannel(Channel *channel_)
{
    poller::assertinloop();
    int fd = channel_->getfd();
    int status = channel_->getstatus();
    assert(channels[fd] == channel_);
    int n = channels.erase(fd);
    assert(n == 1);
    if (status == KAdded)
    {
        update(EPOLL_CTL_DEL, channel_); //如果在监听中删除
    }
}
void poller::update(int operation, Channel *channel_)
{
    struct epoll_event event;
    explicit_bzero(&event, sizeof(event));
    event.events = channel_->getevent();
    event.data.ptr = channel_;
    int fd = channel_->getfd();
    if (epoll_ctl(epfd, operation, fd, &event) < 0)
    {
        LOG(lev::ERROR) << "Epoller::update epoll_ctl the socket fd is " << fd
                                                                          << "and the event is "
                                                                          << (event.events & EPOLLIN ? "EPOLLIN" : " ")
                                                                          << (event.events & EPOLLOUT ? "EPOLLOUT" : " ") << endl;
    }
}
bool  poller::haschannel(Channel *channel)
{   
    channelmap::iterator it=channels.find(channel->getfd());
    return it!=channels.end();
}
void poller::assertinloop()
{
    loop->assertInLoopThread();
}
void poller::fillActiveChannels(int numEvents,
                        channelist *activeChannels) const
{
    for(int i=0;i<numEvents;i++)
    {
        Channel* t=static_cast<Channel*>(list[i].data.ptr);
        int fd=t->getfd();
        t->setevent(list[i].events);
        activeChannels->push_back(t);
    }
}