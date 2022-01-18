#ifndef THREAD_H
#define THREAD_H
#include "nocopy.h"
#include <atomic>
#include <functional>
#include <future>
#include <string>
#include <thread>
namespace yb
{
    class thread : nocopy
    {
        typedef std::function<void()> threadfunc;

    public:
        explicit thread(threadfunc& t,const std::string &s);
        ~thread();
        thread(thread&& s); 
        void getid();
        void join();
        bool start();
        void getname();
        static int runthread();

    private:
        pthread_t thd;
        pid_t tid;
        bool start;
        threadfunc funt;
        std::string name;
        static std::atomic<int> numthreads;
    };
    int getid();
}
#endif