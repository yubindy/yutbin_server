#ifndef TIMEQUEUE_H
#define TIMEQUEUE_H
#include "Timestamp.hpp"
#include "Callback.hpp"
#include "nocopy.hpp"
#include <vector>
#include <set>
#include "Timer.hpp"
#include "Channel.hpp"
namespace yb
{
    class Timer;
    namespace net
    {
        class Eventloop;
        class channel;
        class Timequeue : nocopy
        {
        public:
            explicit Timequeue(Eventloop *loop_);
            ~Timequeue();
            Timer addTimer(Timercallback cb,
                           Timestamp when,
                           double interval);

            void cancel(Timer timerId);

        private:
            typedef std::pair<Timestamp, Timer *> Entry;
            typedef std::set<Entry> TimerList;
            typedef std::pair<Timer *, int64_t> ActiveTimer;
            typedef std::set<ActiveTimer> ActiveTimerSet;
            typedef std::unique_ptr<Timer> Timerptr;
            void addTimerInLoop(Timerptr timer);
            // void cancelInLoop(TimerId timerId);
            // called when timerfd alarms
            void handleRead();
            // move out all expired timers
            std::vector<Entry> getExpired(Timestamp now);
            void reset(const std::vector<Entry> &expired, Timestamp now);

            bool insert(Timer *timer);

            Eventloop *loop;
            const int timerfd;
            Channel timerfdChannel;
            // Timer list sorted by expiration
            TimerList timers;
            // for cancel()
            ActiveTimerSet activeTimers;
            bool callingExpiredTimers; /* atomic */
            ActiveTimerSet cancelingTimers;
        };
    }
}
#endif