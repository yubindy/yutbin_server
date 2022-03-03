#include "poller.h"
using namespace yb;
using namespace yb::net;

poller::poller(Eventloop *loop_) : epfd(epoll_create1(EPOLL_CLOEXEC)), loop(loop_)
{
    if (epfd < 0)
    {
        LOG(lev::ERROR) << "poller:epoll_create1" << endl;
    }
}
Timestamp poller::poll(int timeoutMs, channelist *activeChannels)
{
    int num = epoll_wait(epfd, &*list.begin(), static_cast<int>(list.size()), timeoutMs);
    Timestamp now(Timestamp::now());
    return -1;
}
void updatechannel();
{
}
void removechannel()
{
}

void assertinloop()
{
}