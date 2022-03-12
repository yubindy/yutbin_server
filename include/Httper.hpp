#ifndef HTTPGET_H
#define HTTPGET_H
#include <unordered_map>
#include <string>
#include <memory>
#include "netbuffer.hpp"
namespace yb
{

    namespace http
    {

        enum method
        {
            GET = 0,
            POST,
            // HEAD,
            // PUT,
            // PATCH,
            // DELETE,
            // TRACE,
            // CONNECT,
            DONT_UNDERSTAND,
        };
        class Httpline //请求行
        {
        public:
            enum linestate
            {
                method_,
                url_,
                version_
            };
            Httpline(std::string version_ = "HTTP/1.1") : version(version_){};
            void setmethod(method mod_) { mod = mod_; }
            void seturl(std::string url_) { url = std::move(url_); }
            void setversion(std::string version_) { version = std::move(version_); }
            std::string geturl() { return url; }
            std::string getversion() { return version; }
            method getmethod() { return mod; }
            const char *getstringmethod() { return httpstringmethod[mod]; }
            void debug();
            void setnow(linestate t) {statnow=t;}

        private:
            linestate statnow;
            method mod;          //请求方法
            std::string url;     // url
            std::string version; //版本号
            static const char *httpstringmethod[method::DONT_UNDERSTAND];
        };
        class Httphead //请求头部
        {
        public:
            Httphead() = default;
            void add(std::string key, std::string value) { head.insert(key, value); }
            void remove(std::string key) { head.erase(key); }
            std::string getvalue(std::string key) { return head[key]; }
            void debug()
            {
                LOG(lev::DEBUG) << "Httphead" << endl;
                for_each(head.begin(), head.end(), [](const std::pair<std::string, std::string> &pt)
                         { LOG(lev::DEBUG) << "key" << pt.first << "value" << pt.second << endl; });
            }

        private:
            std::unordered_map<std::string, std::string> head;
        };
        class Httpmessage
        {

        public:
            Httpmessage() = default;
            void setmessage(std::string message_) { message = std::move(message_); }

        private:
            std::string message;
        };
        class HttpRequestate //状态机
        {
        public:
            HttpRequestate() : state(0) {}
            int state;
            Httpline line;
            Httphead head;
            Httpmessage message;
        };
        class Httper : nocopy
        {
        public:
            enum totalstate
            {
                success,
                fail,
                continues,
            };
            enum linestate
            {
                linesuccess,
                linefail,
                linecontinue,
            };
            Httper(const char *buf_, int len_) : buf(buf_), len(len_), pt(0), m_end(0), m_beg(0), end(continues), line(linecontinue), request(new HttpRequestate()) {}
            void requestline();
            void requesthead();
            void requestmessage(int len);

        private:
            const char *CR_LF = "\r\n";
            const char *buf;
            int len;
            int pt; //当前索引
            int m_end;
            int m_beg;
            totalstate end;
            linestate line;
            std::shared_ptr<HttpRequestate> request;
        };
    }
}
#endif