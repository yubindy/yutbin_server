#ifndef POLLER_H
#define POLLER_H
#include <sys/epoll.h>
#include<sys/poll.h>
#include "logging.hpp"
#include "Channel.hpp"
#include "nocopy.hpp"
#include "Eventloop.hpp"
#include <unordered_map>
#include <vector>
#include "Timestamp.hpp"
namespace yb
{
    namespace net
    {
        class Channel;
        class Eventloop; 
        class poller : nocopy
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
            void update(int operation, Channel *channel_);
            channelmap channels;
            int epfd;
            Eventloop *loop;
            eventlist list;
        };
    }
}
#endif