#ifndef LOGGING_H
#define LOGGING_H
#include <stdio.h>
#include "logstream.h"
#include "Timestamp.h"
#include <typeinfo>
#include "Timezone.h"
#include <functional>
const char *strerror_mr(int err);
class Timezone;

namespace yb
{
    logstream &endl(logstream &stream);
    class logger
    {
    public:
        logger();
        enum loglevel
        {
            TRACE,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            NUM_LOG_LEVELS
        };
        class sourcefile //处理传入的路径
        {
        public:
            template <int N>
            sourcefile(const char (&a)[N]) : data(a), size(N - 1)
            {
                const char *t = strrchr(data, '/');
                if (t)
                {
                    data = t + 1;
                    size -= static_cast<int>(data - a);
                }
            }
            sourcefile(const char *filename) : data(filename)
            {
                const char *t = strrchr(data, '/');
                if (t)
                {
                    data = t + 1;
                    size = static_cast<int>(strlen(data));
                }
            }
            const char *data;
            int size;
        };
        logger(sourcefile file_, int line_, const char *func_, int logerrno, loglevel level_ = INFO);
        ~logger();
        using FlushFunc = std::function<void()>;
        using OutputFunc = std::function<void(const char *msg, int len)>;
        static loglevel getlevel() { return level; }
        logstream &getstream() { return streams; }
        static void setLogLevel(loglevel level_);
        static void setOutput(OutputFunc);
        static void setFlush(FlushFunc);
        static void setTimeZone(const Timezone &tz);
        void formatTime();
        Timestamp time;
        sourcefile basename;
        size_t line;
        const char *func;
        logstream streams;
        int errnos;
        static loglevel level;
    };
    extern logger::loglevel loglev;
    using lev = logger::loglevel;
#define Showerr(err,str)  \
    if (err)   \
        fprintf(stderr, "[ERROR]: %s %s", str, strerror(errno));
#define LOG(level)       \
    if (level >= loglev) \
        yb::logger(__FILE__, __LINE__, __func__, (level == logger::loglevel::ERROR || logger::loglevel::FATAL) ? errno : 0, level).streams

}
#endif