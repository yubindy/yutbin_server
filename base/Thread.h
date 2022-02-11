#ifndef THREAD_H
#define THREAD_H
#include "nocopy.h"
#include "atomic.h"
#include <cassert>
#include <functional>
#include <future>
#include <thread>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
namespace yb
{
    class Thread : nocopy
    {
        typedef std::function<void()> threadfunc;

    public:
        explicit Thread(threadfunc &&t, const std::string &&s);
        ~Thread();
        int joins();
        void starts();
        pthread_t *thd;
        bool start;
        bool join;
    private:
        pid_t tid;
        threadfunc funt;
        std::string name;
        std::promise pro;
        static std::atomic<int> numthreads;
    };
    pid_t getid();
}
#endif