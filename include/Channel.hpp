#ifndef CHANNEL_H
#define CHANNEL_H
#include "Callback.hpp"
#include "nocopy.hpp
#include <memory>
#include <vector>
#include <functional>
#include "Eventloop.hpp"
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
        class Channel : nocopy
        {
            using eventback = std::function<void()>;
            using channelist = std::vector<Channel *>;

        public:
            Channel(Eventloop *loop_, int fd_);
            ~Channel();
            void setreadback(eventback t)
            {
                rb = std::move(t);
            }
            void serwruteback(eventback t)
            {
                rb = std::move(t);
            }
            void setcloseback(eventback t)
            {
                rb = std::move(t);
            }
            void seterrorback(eventback t)
            {
                rb = std::move(t);
            }
            void enableReading()
            {
                events_ |= kReadEvent;
                update();
            }
            void disableReading()
            {
                events_ &= ~kReadEvent;
                update();
            }
            void enableWriting()
            {
                events_ |= kWriteEvent;
                update();
            }
            void disableWriting()
            {
                events_ &= ~kWriteEvent;
                update();
            }
            void disableAll()
            {
                events_ = kNoneEvent;
                update();
            }
            bool isWriting() const { return events_ & kWriteEvent; }
            bool isReading() const { return events_ & kReadEvent; }
            bool noEvent() const { return events_ == kNoneEvent; }
            int getfd() { return fd; }
            int getstatus() { return status; }
            void setstatus(int status) {}
            bool isNoneEvent();
            int getevent() { return events_; }
            void setevent(int opt) { recvevents_ = opt; }
            void tie(const std::shared_ptr<void> &pt);
            void handleEvent(Timestamp recvtime);
            void handleEVentwithguard(Timestamp recvtime);
            std::string reventsToString();
            void remove();

        private:
            void update();
            Eventloop *loop;
            int events_;
            int recvevents_;
            const int fd;
            eventback rb;
            int status;
            std::weak_ptr<void> tie_;
            bool tied_;
            static const int kNoneEvent;
            static const int kReadEvent;
            static const int kWriteEvent;

            eventback readCallback_;
            eventback writeCallback_;
            eventback closeCallback_;
            eventback errorCallback_;
        };
    }
}
#endif