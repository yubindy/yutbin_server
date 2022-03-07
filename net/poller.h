#ifndef POLLER_H
#define POLLER_iH
#include <sys/epoll.h>
#include "../base/logging.h"
#include "Channel.h"
#include "../base/nocopy.h"
#include "Eventloop.h"
#include <unordered_map>
#include <vector>
#include "../base/Timestamp.h"
namespace yb
{
    namespace net
    {
        class channel;
        class Eventloop;
        class poller : nocopy //只支持epoll
        {
        public:
            static const int initnum = 36;
            using channelist = std::vector<Channel *>;
            typedef std::unordered_map<int, Channel *> channelmap; // fd->channel 映射
            typedef std::vector<struct epoll_event> eventlist;
            poller(Eventloop *loop_);
            ~poller();
            void updatechannel(Channel *channel_);
            void removechannel(Channel *channel_);
            bool haschannel(Channel *channel);
            Timestamp poll(int timeoutMs, channelist *activeChannels);
            void assertinloop();

        private:
            static const char *operationToString(int op);

            void fillActiveChannels(int numEvents,
                                    channelist *activeChannels) const;
            void update(int operation, channel *channel_);
            channelmap channels;
            int epfd;
            Eventloop *loop;
            eventlist list;
        };
    }
}
#endif