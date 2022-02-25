#ifndef THREADPOOL.H
#define THREADPOOL.H
#include <mutex>
#include <functional>
#include <memory>
#include <vector>
#include <condition_variable>
#include <atomic>
#include "Thread.h"
#include "lockfree_queue.h"
class lf_queue;
namespace yb
{
    class threadpool
    {
    private:
        typedef std::function<void()> task;
        // std::unique_lock<std::mutex> mut;
        // std::condition_variable cod;
        std::shared_ptr<lf_queue<task>> que;
        int threadnum;
        std::atomic<bool> start;
        std::vector<std::unique_ptr<std::thread>> thd;

    public:
        threadpool(int num) : threadnum(num)
        {
            que = std::make_shared(new lf_queue<task>);
            for (int i = 0; i < threadnum; i++)
            {
                thd.emplace_back(new yb::Thread(std::bind(threadpool::take, this), static_cast<int> i));
            }
            start.store(true);
        }
        void take()
        {
            while (start.load())
            {
                while (que->isempty())
                {
                }
                task t(que->pop());
                if(t)
                {
                    t();
                }
            }
        }
        void add(task &&t)
        {
            if(start.store())
            {
                que->push(t);
            }

        }
        ~threadpool() { start.store(false); }
    };
}
#endif