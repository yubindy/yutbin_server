#ifndef INETADDRESS_H
#define INETADDRESS_H
#include "socket.h"
#include <string>
#include <netinet/in.h>
class Socket;
namespace yb
{
    namespace net
    {
        class InetAddress
        {
        public:
            explicit InetAddress(const char *ip, uint16_t port);
            explicit InetAddress(const struct sockaddr_in &addr_) : addr(addr_) {}
            std::string toIp() const;
            std::string toIpPort() const;
            std::string toPortString() const;
            uint16_t toPort() const;
            const struct sockaddr *getSockAddr() const { return static_cast<sockaddr*>(static_cast<void*>(const_cast<sockaddr_in*>(&addr))); }

        private:
            struct sockaddr_in addr;
        };
    }
}
#endif