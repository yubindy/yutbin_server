#include "EventloopThreadpool.hpp"
using namespace yb;
using namespace yb::net;
EventloopThreadpool::EventloopThreadpool(Eventloop *baseLoop) : baseLoop_(baseLoop),
                                                                started_(false), numThreads_(0), next_(0) {}
Eventloop *EventloopThreadpool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    Eventloop *loop = NULL;
    if (!loops_.empty())
    {
        loop = loops_[next_];
        ++next_;
        next_ %= loops_.size();
        return loop;
    }
}
void EventloopThreadpool::start(const ThreadInitback &cb)
{
    assert(!started_);
    baseLoop_->assertInLoopThread();
    started_ = true;
    for (int i = 0; i < numThreads_; i++)
    {
       EventloopThread* t=new EventloopThread(cb);
       threads_.push_back(std::unique_ptr<EventloopThread>(t));
       loops_.push_back(t->startloop());
    }
    if (numThreads_ == 0 && cb)
        cb(baseLoop_);
}
std::vector<Eventloop *> EventloopThreadpool::getAllLoops()
{
    baseLoop_->assertInLoopThread();
    if (loops_.empty())
    {
        return std::vector<Eventloop *>(1, baseLoop_);
    }
    else
    {
        return loops_;
    }
}
