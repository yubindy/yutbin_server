#ifndef LOGSTREAM_H
#define LOGSTREAM_H
#include <string.h>
#include<assert.h> 
#include "nocopy.h"
#include<stdio.h>
#include<string>
namespace yb
{
    const int logsmallbuffer = 4000;
    const int loglargebuffer = 4000 * 1000;
    template <size_t size>
    class logbuffer
    {
    public:
        logbuffer() : len(0) {}
        void addlen(size_t add) { len += add; }
        size_t avail()
        {
            assert(size >= len);
            return size - len;
        };
        const char *debugString(bool out_to_std = true)
        {
            if (!strchr(buf, '\0'))
                buf[len] = '\0';
            if (out_to_std)
            {
                fprintf(stderr, "buf:%s\nsize:%d\n", buf, len);
            }
            for (size_t i = 0; i < len; i++)
            {
                fprintf(stderr, "%d: %c %d\n", i, buf[i], buf[i]);
            }
            return buf;
        }
        void setlen(size_t len_)
        {
            assert(len_ < size);
            len = len_;
            buf[len] = '\0';
        }
        void append(const char *str, size_t len_)
        {
            if (!len_)
                return;
            assert(len_ <= avail());
            memcpy(buf, str, len_);
            addlen(len_);
        }
        void append(char c)
        {
            assert(1 <= avail());
            buf[len] = c;
            addlen(1);
        }
        void append(std::string str, size_t len_)
        {
            if (!len)
                return;
            assert(len_ <= avail());
            memcpy(buf, str.c_str(), len_);
            addlen(len_);
        }
        void reset()
        {
            explicit_bzero(buf, size);
            setlen(0);
        }
        char *stringend() { return buf + len; }
        const char *stringend() const { return buf + len; }
        char *begin() { return buf; }
        const char *begin() const { return buf; }
        const std::string toString() { return std::string(buf, len); }
        size_t sizes() const { return len; }

    private:
        const char *end() const { return buf + sizeof(buf); }
        char buf[size];
        int len;
    };
    class logstream : nocopy
    {
    public:
        static const int kMaxNumericSize = 48;
        friend logstream &endl();
        typedef logstream self;
        typedef logbuffer<logsmallbuffer> logbuf;
        template <typename T>
        void formatint(T v);
        self &operator<<(logbuf &str)
        {
            if (buf_.avail() >= str.sizes())
            {
                buf_.append(str.begin(), str.sizes());
            }
            return *this;
        }
        self &operator<<(self &(*p)(self &stream)) { return p(*this); }
        self &operator<<(short);
        self &operator<<(int);
        self &operator<<(bool v)
        {
            buf_.append(v ? "1" : "0", 1);
            return *this;
        }
        self &operator<<(unsigned short);
        self &operator<<(unsigned int);
        self &operator<<(long);
        self &operator<<(unsigned long);
        self &operator<<(long long);
        self &operator<<(unsigned long long);
        self &operator<<(const void *);
        self &operator<<(float);
        self &operator<<(double);
        self &operator<<(char v)
        {
            buf_.append(v);
            return *this;
        }
        self &operator<<(const char *str)
        {
            if (str)
            {
                buf_.append(str, strlen(str));
            }
            else
            {
                buf_.append("(null)", 6);
            }
            return *this;
        }
        self &operator<<(const unsigned char *v)
        {
            return *this << (reinterpret_cast<const char *>(v));
        }
        self &operator<<(const std::string &str)
        {
            buf_.append(str, str.size());
            return *this;
        }
        logbuf &getBuf() { return buf_; }
        void resetBuffer() { buf_.reset(); }
        using outFunc = void (*)(const char *str, size_t len);
        void setGout(outFunc func);

    private:
        logbuf buf_;
    };
}
#endif