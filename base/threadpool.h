#ifndef THREADPOLL.H
#define THREADPOLL .H
#include "lockfree_queue.h"
#include<
class lf_queue;
class threadpool
{
private:
    lf_queue *que;
    std::unique_lock mut;
    
public:
};
#endif