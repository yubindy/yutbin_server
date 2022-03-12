#include "Httpserver.hpp"
#include "asynclogging.hpp"
#include <stat.h>
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
        int fd = saveurl(url, st, respond);
        if (fd < 0)
        {
            conn->forceClose(); //关闭
            return;
        }
        respond.addContentSize(st.st_size);
        respond.linkFileFd(fd);
        LOG(lev::INFO) << url << "(" << st.st_size << "bytes)"
                       << " will send to user." << endl;
        respond.addContentType("text/html;charset=utf-8");
        respond.respond(); //发送
    }
    else if (request->line.getmethod() == POST)
    {
        fileadd file("./source/" + std::to_string(rand()) + ".txt");
        file.append(request->message.message.c_str(), request->message.message.size());
        respond.setStatusCode(http::HttpResponse::_200);
        respond.addContentType("text/html;charset=utf-8");
        respond.setBody("which your sended have saved as ./source" + url);
        respond.respond();
    }
}
int HttpServer::saveurl(std::string &url, struct stat &ft, HttpResponse &respond)
{
    url = "./source" + url;
    if (url == "./source")
        url += "index.html";
    int fd = open(url.c_str(), O_RDONLY);
    if (fd == -1 || lstat(url.c_str(), &st) || !S_ISREG(stst.mode))
    {
        LOG(lev::ERROR) << "open" << url << "failed" << endl;
        url = "./source/404.html";
        fd = open(url.c_str(), O_RDONLY);
        if (fd == -1 || lstat(url.c_str(), &st))
        {
            LOG(lev::ERROR) << "open " << url << "failed" << endl;
        }
        respond.setStatusCode(HttpResponse::_404);
    }
    else
        respond.setStatusCode(HttpResponse::_200);
    return fd;
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