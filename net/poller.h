#ifndef POLLER_H
#define POLLER_iH
#include <sys/epoll.h>
#include "../base/logging.h"
#include "channel.h"
#include "../base/nocopy.h"
#include "Eventloop.h"
#include <unordered_map>
#include <vector>
#include "../base/Timestamp.h"
class channel;
class Eventloop;
namespace yb
{
    namespace net
    {
        class poller : nocopy //只支持epoll
        {
        public:
            static const int initnum = 36;
            typedef std::unordered_map<int, channel *> channelmap; // fd->channel 映射
            typedef std::vector<struct epoll_event> eventlist;
            poller(Eventloop *loop_);
            ~poller();
            void updatechannel();
            void removechannel();
            Timestamp poll(int timeoutMs, channelist *activeChannels);
            void assertinloop();
        private:
            static const char *operationToString(int op);

            void fillActiveChannels(int numEvents,
                                    channelist *activeChannels) const;
            void update(int operation, channel *channel);
            int epfd;
            Eventloop *loop;
            eventlist list;
        };
    }
}
#endif