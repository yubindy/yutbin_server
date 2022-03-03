#ifndef CHANNEL_H
#define CHANNEL_H
#include <functional>
#include<nocopy.h>
#include<memory>
#include<vector>
#include"Eventloop.h"
namespace yb
{
    namespace net
    {
        class Eventloop;
        class channel:nocopy
        {
        using readback = std::function<void()>;
        public:
            channel(Eventloop *loop_, int fd_);
            void setreadback(readback t);
        private:
            Eventloop *loop;
            int fd;
            readback rb;
        };
        using channelist=std::vector<channel>;
    }
}
#endif