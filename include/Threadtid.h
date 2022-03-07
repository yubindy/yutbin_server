#ifndef THREADTID_H
#define THREADTID_H
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
__thread pid_t tid;
int gettid()
{
    if (tid == 0)
    tid = syscall(SYS_gettid);
    return tid;
}
#endif
