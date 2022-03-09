#ifndef EVENTLOOPTHREAD_H
#define EVENTLOOPTHREAD_H
#include "Eventloop.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
namespace yb
{
    namespace net
    {
        class Eventloop;
        class EventloopThread : nocopy
        {
        public:
            using ThreadInitCallback = std::function<void(Eventloop *)>;
            EventloopThread(const ThreadInitCallback &cb = ThreadInitCallback());
            ~EventloopThread();
            Eventloop *startloop();
        private:
            void threadfunc();
            std::atomic<bool> exiting_;
            Eventloop *loop_;
            std::thread thread_;
            std::mutex mut_;
            std::condition_variable cond_;
            ThreadInitCallback callback_;
        };
    }

}
#endif