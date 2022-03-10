#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <mutex>
#include <functional>
#include <memory>
#include <vector>
#include <condition_variable>
#include <atomic>
#include <thread>
#include "lockfree_queue.hpp"
class lf_queue; //无锁版本
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
            que = std::make_shared<lf_queue<task>>();
            for (int i = 0; i < threadnum; i++)
            {
                thd.emplace_back(new std::thread(std::bind(&threadpool::take, this)));
            }
            start.store(true);
        }
        void take()
        {
            while (start.load())
            {
                if (que->isempty())
                {
                    que->trypop();
                }
                task t(que->pop());
                if (t)
                {
                    t();
                }
            }
        }
        void add(task &t)
        {
            if (start.load())
            {
                if (que->isempty())
                {
                    task();
                }
                que->push(std::move(t));
            }
        }
        ~threadpool() { start.store(false); }
    };
}
#endif