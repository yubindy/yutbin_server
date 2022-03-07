#ifndef EVENTLOOP_h
#define EVENTLOOP_h
#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include "poll.h"
#include "Channel.h"
#include "Timestamp.h"
#include "poller.h"
#include <mutex>
#include "logging.h"
#include "Threadtid.h"
#include "nocopy.h"
#include <sys/eventfd.h>
#include "Tcpconnection.h"
namespace yb
{
    namespace net
    {
        class poller;
        class Channel;
        class Tcpconnection;
        class Eventloop : nocopy, public std::enable_shared_from_this<Eventloop>
        {
        public:
            using Function = std::function<void()>;
            Eventloop();
            ~Eventloop();
            void init();
            void loop(); /* 循环 epoll_wait */
            void quit(); /* 退出 */
            void runInLoop(Function fun);
            void queueInLoop(Function fun);

            void wakeup();
            void updateChannel(Channel *channel);
            void removeChannel(Channel *channel);
            bool hasChannel(Channel *channel);

            void addConnect(std::shared_ptr<Tcpconnection> con);
            void rmConnect(std::shared_ptr<Tcpconnection> con);
            void addConnectInLoop(std::shared_ptr<Tcpconnection> con);
            void rmConnectInLoop(std::shared_ptr<Tcpconnection> con);
            void assertInLoopThread();
            bool isInLoopThread() const { return threadid == gettid(); }

        private:
            void handleRead();        //用于 读取Wakeupfd 为了唤醒所发送的内容
            void doPendingFunctors(); /* 执行小任务函数 */

            bool isMainLoop();
            using channelist = std::vector<Channel *>;
            using Functlist = std::vector<Function>;
            bool loop_;
            std::atomic<bool> quit_;
            bool eventHandling_;          //是否事件循环
            bool callingPendingFunctors_; //是否处理后续任务
            const pid_t threadid;
            int wakefd;
            std::unique_ptr<Channel> wakechannel_;
            std::unique_ptr<poller> poller_;
            Timestamp polltime;
            mutable std::mutex mutex_;
            Channel *curractivechannel;
            channelist activelist;
            Functlist pendinglist;
        };
    }
}
#endif