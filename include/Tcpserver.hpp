#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "nocopy.hpp"
#include "EventloopThread.hpp"
#include "TcpConnection.hpp"
#include <memory>
#include<map>
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
            using ThreadInitback = std::function<Eventloop *>;
            Tcpserver(Eventloop *loop, const InetAddress address, const string &name, int numthread = 4); //默认4 i/o线程
            ~Tcpserver();
            void start();
            const std::string &getip() const { return ip_; }
            const std::string &getport() const { return port_; }
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
            void setThreadInitCallback(const ThreadInitCallback &&cb)
            {
                threadinit_ = std::move(cb);
            }
            void removeConnection(const TcpConnectionPtr &conn);
            void removeConnectionInLoop(const TcpConnectionPtr &conn);
            void newConnection(int sockfd, const InetAddress &peerAddr);
        private:
            using Connectmap=std::map<std::string,Tcpconnection>;
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
        };
    }

}
#endif