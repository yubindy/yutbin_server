#include "EventloopThread.hpp"
using namespace yb;
using namespace yb::net;

EventloopThread::EventloopThread(const ThreadInitCallback &cb)
    : loop_(NULL), exiting_(false), thread_(std::bind(&EventloopThread::threadfunc, this)),
      callback_(cb)
{
    if (!loop_)
    {
        std::unique_lock<std::mutex> lock(mut_);
        cond_.wait(lock, loop_);
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
        std::unique_lock<std::mutex> lock(mut_);
        while (loop_ = NULL)
        {
            cond_.wait(lock, loop_);
        }

        return loop_;
    }
}
void EventloopThread::threadfunc()
{
    Eventloop loop;
    if(callback_)
    {
        callback_(&loop);
    }
    {
         std::unique_lock<std::mutex> lock(mut_);
         loop_=&loop;
         cond_.notify_one();
    }

}
