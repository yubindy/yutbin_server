#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "nocopy.hpp"
#include "EventloopThread.hpp"
#include "TcpConnection.hpp"
#include"Acceptor.hpp"
#include"EventloopThreadpool.hpp"
#include <memory>
#include <map>
#include <atomic>
namespace yb
{
    namespace net
    {
        class Eventloop;
        class Acceptor;
        class EventloopThreadpool;
        class Tcpserver : nocopy
        {
        public:
            using ThreadInitback = std::function<void(Eventloop *)>;
            using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
            Tcpserver(Eventloop *loop, const InetAddress address, const std::string &name, int numthread = 4); //默认4 i/o线程
            ~Tcpserver();
            void start();
            const std::string &getipport() const { return ipport; }
            std::shared_ptr<Eventloop> getloop() const { return mainloop; }
            void setThreadnums(int num);
            void setConnectionback(ConnectionCallback &&cb)
            {
                connback = cb;
            }
            void setMessageback(MessageCallback &&cb)
            {
                messback = cb;
            }

            void setWriteCompleteCallback(WriteCompleteCallback &&cb)
            {
                writeback = std::move(cb);
            }
            void setThreadInitCallback(const ThreadInitback &&cb)
            {
                threadinit_ = std::move(cb);
            }
            void removeConnection(const TcpConnectionPtr &conn);
            void removeConnectionInLoop(const TcpConnectionPtr &conn);
            void newConnection(int sockfd, const InetAddress &peerAddr);

        private:
            using Connectmap = std::map<std::string, TcpConnectionPtr>;
            std::shared_ptr<Eventloop> mainloop;
            const std::string ipport;
            int nextConnId_;
            const std::string name;
            std::unique_ptr<Acceptor> acceptor_;
            std::shared_ptr<EventloopThreadpool> threadpool_;
            ConnectionCallback connback;
            MessageCallback messback;
            WriteCompleteCallback writeback;
            ThreadInitback threadinit_;
            Connectmap connects;
            std::atomic<bool> stared_;
            int threadnum;
        };
    }

}
#endif