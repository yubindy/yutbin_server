#ifndef LOCKFREE_QUEUE.H
#define LOCKFREE_QUEUE .H
#include <atomic.h>
#include <memory>
namespace yb
{
    template <typename T>
    class lf_queue //无锁队列实现
    {
    public:
        class node
        {
        public:
            std::shared_ptr<T> val;
            node *next;
        };
        lf_queue() : front(new node), end(front.load()), cnt(0) {} //也可以使用std::unique_ptr，不是很必要
        lf_queue(const lf_queue &t) = delete;
        lf_queue operator=(const lf_queue &t) = delete;
        ~lf_queue()
        {
            while (node *const old = front.load())
            {
                front.store(old->next);
                delete old;
            }
        }
        int count() { return cnt.load(); }
        bool isempty() { return cnt.load() == 0 ? true : false; }
        void push(T &&num)
        {
            node *newd = new node(make_shared(num), nullptr);
            node *oldode = end.load();
            while (!(oldode->next).compare_exchange_weak(NULL, newd))
            {
                while (oldode->next != nullptr) //避免占用tail挂掉，死循环
                {
                    oldode = oldode->next;
                }
            }
            end.compare_exchange_strong(oldode, newd); //释tail占用
            cnt.fetch_add(1);
        }
        T pop()
        {
            node *beg = front.load();
            if (beg->next == nullptr)
                return nullptr;
            while (!front.compare_exchange_weak(beg, beg->next))
            {
            }
            cnt.fetch_add(-1);
            std::shared_ptr<T> val = beg->val;
            delete beg;
            return *val;
        }

    private:
        std::atomic<node *> front;
        std::atomic<node *> end;
        std::atomic<int> cnt;
    };
}
#endif