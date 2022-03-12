#include "Httpserver.hpp"
#include <stat.h>
#include "asynclogging.hpp"
using namespace yb;
using namespace yb::http;
void HttpServer::Messageback(const Tcpconptr &conn, netbuffer *buf)
{
    const char *t = buf->peek();
    int len = buf->writebyte();
    http::Httper helper(t, len);
    Httper::totalstate finalstate = helper.requestall(); //解析
    LOG(lev::INFO) << "finalstate" << static_cast<int>(finalstate) << "from" << conn->peerAddress().toPortString() << endl;
    auto request = helper.getrequest();
    if (finalstate == Httper::success)
        Successback(conn, request, buf);
    else if (finalstate == Httper::continues)
    {
    }
    else
    {
        buf->retrieveAll();
        conn->shutdown();
    }
}
void HttpServer::Connectionback(const Tcpconptr &conn)
{
    LOG(lev::INFO) << "connection setup..." << endl;
}
void HttpServer::Successback(const Tcpconptr &conn, HttpRequestate *request, netbuffer *buf)
{
    struct stat st;
    HttpResponse respond(conn);
    buf->retrieve(request->state);
    std::string url = request->line.geturl();
    respond.setVersion(request->line.getversion());
    const auto &keeplive_ = request->head.getvalue("Connection");
    bool opt = keeplive_ == "keep-ative" || keeplive_ == "keep-Ative";
    respond.addKeepAlive(opt);
    if (request->line.getmethod() == GET)
    {
        int fd = saveurl(url, &st, respond);
    } 
}
int HttpServer::saveurl(std::string &url, struct stat &ft, HttpResponse &respond)
{
}
int main()
{
    AsyncLogging asynclog("httpserver", 1024 * 1024, 60);
    logger::setLogLevel(lev::INFO);
    asynclog.start();
    const int poolthreads = 10;
    InetAddress addr("127.0.0.1", 8888);
    HttpServer httpserver(poolthreads, addr);
    httpserver.start();
}