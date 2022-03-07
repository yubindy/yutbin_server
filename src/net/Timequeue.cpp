#include "./Timequeue.h"
#include "../base/logging.h"
#include <sys/timerfd.h>
using namespace yb;
using namespace yb::net;
int createTimerfd()
{
    int timerfd = timerfd_create(CLOCK_MONOTONIC,
                                 TFD_NONBLOCK | TFD_CLOEXEC);
    if (timerfd < 0)
    {
        LOG(lev::FATAL)<<"Failed in timerfd_create";
    }
    return timerfd;
}
Timequeue::Timequeue(Eventloop *loop_) : loop(loop_), timerfd(createTimerfd()),timerfdChannel(loop,timerfd),callingExpiredTimers(false)
{
    timerfdChannel.setreadback(std::bind(&Timequeue::handleRead,this));
    timerfdChannel.enablereading();
}
Timequeue::~Timequeue()
{
  timerfdChannel_.disableAll();
  timerfdChannel_.remove();
  close(timerfd_);
}
Timer Timequeue::addTimer(Timercallback cb,
                             Timestamp when,
                             double interval)
{
  Timer* timers = new Timer(std::move(cb), when, interval);
  loop->runInLoop(
      std::bind(&TimerQueue::addTimerInLoop, this, timers));
  return timers;
}
void Timequeue::addTimerInLoop()
{
  loop.
}

                                         // Eventloop * loop_;
                                         // const int timerfd_;
                                         // channel timerfdChannel;
                                         // // Timer list sorted by expiration
                                         // TimerList timers_;
                                         // // for cancel()
                                         // ActiveTimerSet activeTimers_;
                                         // bool callingExpiredTimers_; /* atomic */
                                         // ActiveTimerSet cancelingTimers_;