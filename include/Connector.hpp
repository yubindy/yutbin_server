#ifndef Connector_H
#define Connector_H
#include "nocopy.hpp"
#include "InetAddress.hpp"
#include "functional"
#include "Eventloop.hpp"
#include "logging.hpp"
#include <memory>
namespace yb
{

    namespace net
    {
        class Channel;
        class Eventloop;
        class Connector : nocopy,
                          public std::enable_shared_from_this<Connector>
        {
        public:
            using NewConnectionCallback = std::function<void(int sockfd)>;
            Connector(Eventloop *loop, const InetAddress &serverAddr);
            ~Connector();
            void setNewConnectionCallback(const NewConnectionCallback &cb)
            {
                newConnectionCallback_ = cb;
            }
            void Start();   // can be called in any thread
            void restart(); // must be called in loop thread
            void stop();    // can be called in any thread
            const InetAddress &serverAddress() const { return serverAddr_; }

        private:
            enum States
            {
                kDisconnected,
                kConnecting,
                kConnected
            };
            static const int kMaxRetryDelayMs = 30 * 1000;
            static const int kInitRetryDelayMs = 500;

            void setState(States s) { state_ = s; }
            void startInLoop();
            void stopInLoop();
            void connect();
            void connecting(int sockfd);
            void handleWrite();
            void handleError();
            void retry(int sockfd);
            int removeAndResetChannel();
            void resetChannel();
            Eventloop *loop_;
            InetAddress serverAddr_;
            bool connect_;
            States state_;
            std::unique_ptr<Channel> channel_;
            NewConnectionCallback newConnectionCallback_;
        };
    }
}
#endif
