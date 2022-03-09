#ifndef EVENTLOOPTHREADPOOL_H
#define EVENTLOOPTHREADPOOL_H
#include "EventloopThread.hpp"
#include "nocopy.hpp"
#include <memory>
#include <vector>
#include <functional>
namespace yb
{
    namespace net
    {
        class EventloopThreadpool : nocopy
        {
        public:
            using ThreadInitback = EventloopThread::ThreadInitCallback;
            EventloopThreadpool(Eventloop* baseLoop);
            ~EventloopThreadpool() = default;
            Eventloop* getNextLoop();
            // EventLoop* getLoopForHash(size_t hashCode);
            std::vector<Eventloop*> getAllLoops();

            void setThreadNum(int numThreads) { numThreads_ = numThreads; }
            void start(const ThreadInitback &cb = ThreadInitback());
            bool started() const { return started_; }

        private:
            int numThreads_;                      /* 线程数 */
            Eventloop* baseLoop_; /* mainloop */
            std::atomic<bool> started_;           /* 开始了么 */
            int next_;                            /* 轮询的下一个的坐标 */
            std::vector<std::unique_ptr<EventloopThread>> threads_;
            std::vector<Eventloop*> loops_;
        };
    }
}
#endif
