#ifndef CALLBACK_H
#define CALLBACK_H
#include "../base/Timestamp.h"
#include <functional>
#include <memory>
namespace yb
{
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    namespace net
    {
        class netbuffer;
        class Tcpconnect;
        using Tcpconptr = std::shared_ptr<Tcpconnect>;
        using Timercallback = std::function<void()>;
        using ConnectionCallback = std::function<void(const Tcpconptr &)>;
        using CloseCallback = std::function<void(const Tcpconptr &)>;
        using WriteCompleteCallback = std::function<void(const Tcpconptr &)>;
        using MessageCallback = std::function<void(const Tcpconptr &,
                                                   netbuffer *, Timestamp)>;
        void defaultConnectionCallback(const Tcpconptr &conn);
        void defaultMessageCallback(const Tcpconptr &conn,
                                    netbuffer *buffer,
                                    Timestamp receiveTime);
    }
}
#endif;