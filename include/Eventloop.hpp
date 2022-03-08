#ifndef EVENTLOOP_h
#define EVENTLOOP_h
#include <vector>
#include <functional>
#include <memory>
#include <atomic>
#include "Channel.hpp"
#include "Timestamp.hpp"
#include "poller.hpp"
#include <mutex>
#include "logging.hpp"
#include "Threadtid.hpp"
#include "nocopy.hpp"
#include <sys/eventfd.h>
#include "Tcpconnection.hpp"
#include "Socket.hpp"
namespace yb
{
    namespace net
    {

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