#ifndef CHANNEL_H
#define CHANNEL_H
#include <functional>
#include <nocopy.h>
#include <memory>
#include <vector>
#include "Eventloop.h"
namespace yb
{
    namespace net
    {
        class Eventloop;
        enum
        {
            kNew,
            KAdded,
            kDeleted,
        };
        class channel : nocopy
        {
            using readback = std::function<void()>;

        public:
            channel(Eventloop *loop_, int fd_);
            void setreadback(readback t);
            int getfd();
            int getstatus();
            void setstatus(int status);
            bool isNoneEvent();
            int getevent();
            void setevent(int opt);
             private : Eventloop *loop;
            int fd;
            readback rb;
        };
        using channelist = std::vector<channel*>;
    }
}
#endif