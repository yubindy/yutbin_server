#include "Eventloop.h"
using namespace yb;
using namespace yb::net;
namespace
{
    __thread net::Eventloop *t_loopInThisThread = 0;
    int createEventfd()
    {
        int evfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
        if (evfd < 0)
        {
            LOG(lev::FATAL) << "createEventfd error" << endl;
        }
        return evfd;
    }
}
const int kPollTimeMs = 10000;
Eventloop::Eventloop() : loop_(false), quit_(false), eventHandling_(false), callingPendingFunctors_(false), threadid(gettid()),
                         wakefd(createEventfd()), wakechannel_(new Channel(this, wakefd)), poller_(new poller(this))
{
    if (t_loopInThisThread)
    {
        LOG(lev::FATAL) << "Another EventLoop " << t_loopInThisThread
                        << " exists in this thread " << threadid << endl;
    }
    else
    {
        t_loopInThisThread = this;
    }
    wakechannel_->setreadback(std::bind(&Eventloop::handleRead, this));
    wakechannel_->enableReading();
}
Eventloop::~Eventloop()
{
    wakechannel_->disableAll();
    wakechannel_->remove();
    close(wakefd);
}
void Eventloop::loop()
{
    quit_.store(false);
    while (quit_.load())
    {
        activelist.clear();
        polltime = poller_->poll(kPollTimeMs, &activelist);
        eventHandling_ = true;
        for (Channel *chan : activelist)
        {
            curractivechannel = chan;
            curractivechannel->handleEvent(polltime);
        }
        eventHandling_ = false;
        curractivechannel = NULL;
        doPendingFunctors();
    }
}
void Eventloop::removeChannel(Channel *chan)
{
    assertInLoopThread();
    if (eventHandling_)
    {
        assert(curractivechannel == chan);
    }
    poller_->removechannel(chan);
}
void Eventloop::quit()
{
    quit_ = true;
    if (isInLoopThread())
        wakeup();
}
void Eventloop::runInLoop(Function fun)
{
    if (isInLoopThread())
    {
        fun();
    }
    else
    {
        queueInLoop(std::move(fun));
    }
}
void Eventloop::queueInLoop(Function fun)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pendinglist.push_back(fun);
    }
    if (!isInLoopThread() || callingPendingFunctors_)
        wakeup();
}
void Eventloop::wakeup()
{
    uint64_t one;
    ssize_t t = write(wakefd, &one, sizeof one);
    if (t != sizeof(one))
    {
        LOG(lev::ERROR) << "EventLoop::wakeup error" << endl;
    }
}

void Eventloop::updateChannel(Channel *channel)
{
    assertInLoopThread();
    poller_->updatechannel(channel);
}
bool Eventloop::hasChannel(Channel *channel)
{   assertInLoopThread();
    poller_->haschannel(Channel);
}
// bool loop_;
// std::atomic<bool> quit_;
// bool eventHandling_;          //是否事件循环
// bool callingPendingFunctors_; //是否处理后续任务
// const pid_t threadid;
// int wakefd;
// std::unique_ptr<Channel *> wakechannel_;
// std::unique_ptr<poller> poller_;
// Timestamp time;
// mutable std::mutex mutex_;
// Channel *curractivechannel;
// channelist activelist;
// Functlist pendinglist;

// void addConnect(std::shared_ptr<Tcpconnection> con);
// void rmConnect(std::shared_ptr<Tcpconnection> con);
// void addConnectInLoop(std::shared_ptr<Tcpconnection> con);
// void rmConnectInLoop(std::shared_ptr<Tcpconnection> con);

// private:
// void handleRead();        //用于 读取Wakeupfd 为了唤醒所发送的内容
// void doPendingFunctors(); /* 执行小任务函数 */
