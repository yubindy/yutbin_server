#ifndef POLLER.H
#define POLLER .H
#include <sys/epoll.h>
#include "channel.h"
#include "../base/nocopy.h"
#include "Eventloop.h"
#include <unordered_map>
#include <vector>
class channel;
namespace yb
{
    class poller : nocopy
    {
    public:
        static const int initnum = 36;
        typedef std::unordered_map<int, channel *> channelmap;
        typedef std::vector<struct epoll_event> eventlist;
        poller(Eventloop *loop_) : epfd(epoll_create1(EPOLL_CLOEXEC)), loop(loop_)
        {
            if(epfd<0)
            {
                //log
            }
        }
        void update();
        void poll();
        void assertinloop();

    private:
        int epfd;
        Eventloop *loop;
        eventlist list;
    };
}
#endif