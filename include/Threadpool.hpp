#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <deque>
#include "nocopy.hpp"
namespace yb
{
    class ThreadPool : nocopy
    {
    public:
        typedef std::function<void()> Task;

        explicit ThreadPool(const std::string &nameArg = std::string("ThreadPool"));
        ~ThreadPool();
        void setMaxQueueSize(int maxSize) { maxQueueSize_ = maxSize; }
        void setThreadInitCallback(const Task &cb)
        {
            threadInitCallback_ = cb;
        }

        void start(int numThreads);
        void stop();

        const std::string &name() const
        {
            return name_;
        }

        size_t queueSize() const;
        void run(Task f);

    private:
        bool isFull() const;
        void runInThread();
        Task take();

        mutable std::mutex mutex_;
        std::condition_variable notFull_;
        std::condition_variable notEmpty_;
        std::string name_;
        Task threadInitCallback_;
        std::vector<std::unique_ptr<std::thread>> threads_;
        std::deque<Task> queue_;
        size_t maxQueueSize_;
        bool running_;
    };

}