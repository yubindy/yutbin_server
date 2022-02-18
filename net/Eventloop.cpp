#ifndef EVENTLOOP.H
#define EVENTLOOP .H
#include <vector>
#include <atomic>
#include <cassert>
#include <functional>
#include <future>
#include <thread>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include<
#include <sys/types.h>
namespace yb
{
    class Eventloop
    {
    public:
    private:
    bool looping;
    bool quit;
    bool eventhandle;
    bool callpending;
    int loopnum;
    pid_t num;
    epoll
    };
}
#endif