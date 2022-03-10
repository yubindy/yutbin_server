#include "EventloopThread.hpp"
using namespace yb;
using namespace yb::net;

EventloopThread::EventloopThread(const ThreadInitCallback &cb)
    : loop_(NULL), exiting_(false), pt(t.get_future()), thread_(std::bind(&EventloopThread::threadfunc, this)),
      callback_(cb)
{
    if (!loop_)
    {
        pt.get();
    }
}
EventloopThread::~EventloopThread()
{
    exiting_ = true;
    if (loop_)
    {
        loop_->quit();
        thread_.join();
    }
}
Eventloop *EventloopThread::startloop()
{
    {   
        pt=t.get_future();
        pt.get();
        return loop_;
    }
}
void EventloopThread::threadfunc()
{
    Eventloop loop;
    if (callback_)
    {
        callback_(&loop);
    }
    loop_ = &loop;
    t.set_value(true);
}
