#include "Eventloop.h"
using namespace yb;
using namespace yb::net;
Eventloop::Eventloop():loop_(false),quit_(false),eventHandling_(false),callingPendingFunctors_(false),threadid(gettid()){}

// bool loop_;
// std::atomic<bool> quit_;
// bool eventHandling_;          //是否事件循环
// bool callingPendingFunctors_; //是否处理后续任务
// const pid_t threadid;
// int wakefd;
// std::unique_ptr<Channel *> wakechannel_;
// std::unique_ptr<poller> poller_;
// Timestamp time;
// mutable std::mutex mutex_;
// Channel *curractivechannel;
// channelist activelist;
// Functlist pendinglist;