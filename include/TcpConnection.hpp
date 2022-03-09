#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H
#include "netbuffer.hpp"
#include "nocopy.hpp"
#include "Callback.hpp"
#include "InetAddress.hpp"
#include "Timestamp.hpp"
#include "InetAddress.hpp"
#include"Channel.hpp"
namespace yb
{
    namespace net
    {
        class Channel;
        class Eventloop;
        class Socket;
        class TcpConnection : nocopy, public std::enable_shared_from_this<TcpConnection>
        {
        public:
            TcpConnection(Eventloop *loop, int sockfd,const std::string& nameArg,
                          const InetAddress &localAddr, const InetAddress &peerAddr);
            ~TcpConnection();

            Eventloop *getLoop() const { return loop_; }
            const InetAddress &localAddress() const { return localAddr_; }
            const InetAddress &peerAddress() const { return peerAddr_; }
            bool connected() const { return state_ == kConnected; }
            bool disconnected() const { return state_ == kDisconnected; }
            // void send(string&& message); // C++11
            void send(const void *message, int len);
            void send(std::string &message);
            // void send(Buffer&& message); // C++11
            void sendFile(int fd, int fileSize);
            void send(netbuffer *message); // this one will swap data
            void shutdown();               // NOT thread safe, no simultaneous calling
            void shutdownInLoop();
            void forceClose();
            void setTcpNoDelay(bool on);
            // reading or not
            void startRead();
            void stopRead();
            std::string name() const {return name_;}
            bool isReading() const
            {
                return reading_;
            }; // NOT thread safe, may race with start/stopReadInLoop

            void setConnectionCallback(const ConnectionCallback &cb)
            {
                connectionCallback_ = cb;
            }

            void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }

            void setWriteCompleteCallback(const WriteCompleteCallback &cb)
            {
                writeCompleteCallback_ = cb;
            }

            netbuffer *inputBuffer() { return &inputBuffer_; }

            netbuffer *outputBuffer() { return &outputBuffer_; }

            /// Internal use only.
            void setCloseCallback(CloseCallback cb) { closeCallback_ = cb; }

            void debugBuffer()
            {
                LOG(lev::DEBUG) << "outputBuffer_:" << endl;
                outputBuffer_.debug();
                LOG(lev::DEBUG) << "inputBuffer_:" << endl;
                inputBuffer_.debug();
            }
            // called when TcpServer accepts a new connection
            void connectEstablished(); // should be called only once
            // called when TcpServer has removed me from its map
            void connectDestroyed(); // should be called only once

            enum State
            {
                kDisconnected,
                kConnecting,
                kConnected,
                kDisconnecting
            };

        private:
            void handleRead(Timestamp receiveTime);
            void handleWrite();
            void handleClose();
            void handleError();
            void sendInLoop(std::string &&message);
            // void sendInLoop(const StringPiece &message);
            void sendInLoop(const void *message = NULL, size_t len = 0,
                            int sendFileFd = -1, int sendFileSize = 0);
            void sendInLoop(const char *message, size_t len);

            void shutdownWriteInLoop(); /* 关闭写 */
            void forceCloseInLoop();
            void setState(State s) { state_ = s; }
            const char *stateToString() const;
            void startReadInLoop();
            void stopReadInLoop();

            Eventloop *loop_;
            const std::string name_;
            State state_; // FIXME: use atomic variable
            bool reading_;
            // we don't expose those classes to client.
            std::unique_ptr<Socket> socket_;
            std::unique_ptr<Channel> channel_;
            const InetAddress localAddr_;
            const InetAddress peerAddr_;
            ConnectionCallback connectionCallback_;
            MessageCallback messageCallback_;
            WriteCompleteCallback writeCompleteCallback_;
            CloseCallback closeCallback_;
            size_t highWaterMark_;
            netbuffer inputBuffer_;
            netbuffer outputBuffer_; 
            // FIXME: use list<Buffer> as output buffer.
            // FIXME: creationTime_, lastReceiveTime_
            //        bytesReceived_, bytesSent_
            using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
            void defaultMessageCallback(const TcpConnectionPtr &conn, netbuffer *buf);
            void defaultConnectionCallback(const TcpConnectionPtr &conn);
        };

    }
}
#endif