#ifndef INETADDRESS_H
#define INETADDRESS_H
#include "Socket.hpp"
#include <string>
#include <netinet/in.h>
namespace yb
{
    namespace net
    {
        class Socket;
        class InetAddress
        {
        public:
            explicit InetAddress();
            explicit InetAddress(const char *ip, uint16_t port);
            explicit InetAddress(const struct sockaddr_in &addr_) : addr(addr_) {}
            std::string toIp() const;
            std::string toIpPort() const;
            std::string toPortString() const;
            uint16_t toPort() const;
            sa_family_t family() const { return addr.sin_family; }
            const struct sockaddr *getSockAddr() const { return static_cast<sockaddr *>(static_cast<void *>(const_cast<sockaddr_in *>(&addr))); }
            void setSockAddr(struct sockaddr_in addr_) { addr = addr_; }

        private:
            struct sockaddr_in addr;
        };
    }
}
#endif