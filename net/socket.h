#ifndef SOCKET_H
#define SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include "../base/nocopy.h"
#include "InetAddress.h"
namespace yb
{
    namespace net
    {
        class InetAddress;
        int createNonblockingOrDie(sa_family_t family);
        int connect(int sockfd, const struct sockaddr *addr);
        void bindOrDie(int sockfd, const struct sockaddr *addr);
        void listenOrDie(int sockfd);
        int accept(int sockfd, struct sockaddr_in *addr);
        void close(int sockfd);
        void shutdownWrite(int sockfd);
        void shutdownRead(int sockfd);
        void toIpPort(char *buf, size_t size, const struct sockaddr *addr);
        void toIp(char *buf, size_t size, const struct sockaddr *addr);
        void toPortString(char *buf, size_t size, const struct sockaddr *addr);
        void fromIpPort(const char *ip, uint16_t port, struct sockaddr_in *addr);

        int getSocketError(int sockfd);

        struct sockaddr_in getLocalAddr(int sockfd);
        struct sockaddr_in getPeerAddr(int sockfd);
        class Socket : nocopy
        {
        public:
            explicit Socket(int sockfd) : sockfd_(sockfd) {}
            ~Socket() { close(sockfd_); }
            int fd() const { return sockfd_; }
            // bool getTcpINFO_(struct tcp_info *) const;
            // bool getTcpInfoString(char *buf, int len) const;
            void bindAddress(const InetAddress &localaddr);
            void listen();
            int accept(InetAddress *peeraddr);
            void shutdownWrite();
            void shutdownRead();
            void setTcpNoDelay(bool on);
            void setReuseAddr(bool on);
            void setReusePort(bool on);
            void setKeepAlive(bool on);

        private:
            const int sockfd_;
        };

    } // namespace sock
}
#endif