#ifndef POLLER.H
#define POLLER.H
#include <sys/epoll.h>
#include "channel.h"
#include "../base/nocopy.h"
#include"Eventloop.h"
#include <unordered_map>
#include<vector>
class channel;
namespace yb
{
    class poller : nocopy
    {
    public:
        typedef std::unordered_map<int, channel *> channelmap;
        typedef std::vector<channel*> actchannel;
        poller(Eventloop* loop_);
        void update();
        actchannel wait();
    private:
        int epfd;
        Eventloop* loop;
    };
}
#endif