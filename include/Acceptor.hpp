#ifndef ACCEPTOR_H
#define ACCEPTOR_H
#include <nocopy.hpp>
#include <atomic>
#include "InetAddress.hpp"
#include "Channel.hpp"
#include "Socket.hpp"
namespace yb
{
    namespace net
    {
        class Socket;
        class Channel;
        using NewConnectionback = std::function<void(int sockfd, const InetAddress &address)>;
        class Acceptor : nocopy
        {
        public:
            Acceptor(Eventloop *loop, const InetAddress &listenaddr, bool reuseport);
            ~Acceptor();
            void setConnectback(const NewConnectionback &cb)
            {
                NewConnection_ = cb;
            }
            void listen();
            bool listening() const { return listen_; }

        private:
            void handleRead();
            Eventloop *loop;
            Socket acceptsocket;
            Channel acceptChannel;
            NewConnectionback NewConnection_;
            bool listen_;
            int fd_;
        };
    }
}
#endif