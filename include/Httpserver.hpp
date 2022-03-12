#ifndef HTTPSERVER_hpp
#define HTTPSERVER_hpp
#include "nocopy.hpp"
#include "Tcpserver.hpp"
#include"Httper.hpp"
#include"HttpResponse.hpp"
namespace yb
{
    namespace http
    {
        class HttpServer : nocopy
        {
        public:
            HttpServer(net::Tcpserver *server, net::Eventloop *loop) : tcpserver_(server), mainloop(loop) {}
            
        private:
            net::Tcpserver *tcpserver_;
            net::Eventloop *mainloop;
        };
    }
}
#endif