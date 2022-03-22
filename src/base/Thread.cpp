#include "Thread.hpp"
namespace yb
{
    Thread::Thread(threadfunc &&t, const std::string &&s) : thd(nullptr), tid(0), start(false), join(false), name(s), funt(std::move(t))
    {
        numthreads++;
        starts();
    }
    Thread::~Thread() {}
    class threadData
    {
    public:
        typedef std::function<void()> ThreadFunc;
        threadData(ThreadFunc &&funt, std::string &&name, std::promise<void> &p,
                   pid_t &tid)
            : funt_(funt), name_(name), p_(p), tid_(tid) {}
        ~threadData() {}
        ThreadFunc funt_;
        std::string name_;
        pid_t tid_;
        std::promise<void> &p_;
    };
    void *runthread(void *args)
    {
        threadData *t(static_cast<threadData *> (args));
        t->p_.set_value();
        try
        {
            t->funt_();
        }
        catch (const std::exception e)
        {
            fprintf(stderr, "exception caught in Thread %s\n", t->name_.c_str());
            fprintf(stderr, "reason: %s\n", e.what());
        }
        return NULL;
    }
    pid_t getid()
    {
        return syscall(SYS_gettid);
    }
    void Thread::starts()
    {
        threadData *data = new threadData(std::move(funt), std::move(name), pro,tid);
        std::future<void> s = pro.get_future();
        if (pthread_create(thd, nullptr, runthread, static_cast<void *>(data)))
        {
        }
        else
        {
            s.get();
            start = true;
        }
    }
    int Thread::joins()
    {
        assert(!join);
        join = true;
        return pthread_join(tid, nullptr);
    }
}