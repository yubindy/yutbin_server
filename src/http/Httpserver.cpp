#include"Httpserver.hpp"
#include"asynclogging.hpp"
using namespace yb;
using namespace yb::http;
int main()
{
    AsyncLogging asynclog("httpserver",1024*1024,60);
    logger::setLogLevel(lev::INFO);
    asynclog.start();
    InetAddress addr("127.0.0.1",8888);
    HttpServer httpserver(addr);
    httpserver.start();
}