#ifndef HTTPSERVER_hpp
#define HTTPSERVER_hpp
#include "Threadpool.hpp"
#include "nocopy.hpp"
#include "Tcpserver.hpp"
#include "Httper.hpp"
#include "HttpResponse.hpp"
namespace yb
{
    namespace http
    {
        using Task = std::function<void()>;
        class HttpServer : nocopy
        {
        public:
            HttpServer(int poolthreads, InetAddress &addr) : pool(new ThreadPool()), mainloop(new Eventloop()), tcpserver_(new net::Tcpserver(mainloop, addr, "httpserver"))
            {
                pool->start(poolthreads);
            }
            void setMessage(const Tcpconptr &conn, netbuffer *buf);
            void setConnectionback(const Tcpconptr &conn);
            void setSuccessback(const Tcpconptr &conn, const HttpRequestate *request, netbuffer *buf);
            int saveurl(std::string &ur, struct stat &ft, HttpResponse &respond);
            void setthreadpoolback(Task tk) { pool->run(tk) //加入线程池}
            void start()
            {
                tcpserver_->setMessageback(std::bind(&HttpServer::setMessage, this, _1, _2));
                tcpserver_->setConnectionback(std::bind(&HttpServer::setConnectionback, this, _1));
                tcpserver_->start();
            }

        private:
            std::unique_ptr<ThreadPool> pool;
            std::unique_ptr<Eventloop> mainloop;
            std::unique_ptr<net::Tcpserver> tcpserver_;
        };
    }
}
#endif