#include "Eventloop.hpp"
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
void Eventloop::assertInLoopThread() {
  if (!isInLoopThread()) {
    LOG(lev::FATAL) << "not in specified EventLoop"
               << (isMainLoop() ? "(mainLoop)" : "(subLoop)") <<endl;
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
{
    assertInLoopThread();
    poller_->haschannel(channel);
}
void Eventloop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = read(wakefd, &one, sizeof(one));
    if (n != sizeof(one))
    {
        LOG(lev::ERROR) << "EventLoop::handleRead() reads " << n << " bytes instead of 8" << endl;
    }
}
void Eventloop::doPendingFunctors()
{
     Functlist funtors;
     callingPendingFunctors_=true;
     {
        std::lock_guard<std::mutex> lock(mutex_);
        pendinglist.swap(funtors);
    }
    for(const Function&fun:funtors)
    {
        fun();
    }
    callingPendingFunctors_=false;
}
