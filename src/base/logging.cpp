#include "logging.hpp"
#include "Thread.hpp"
#include"logstream.hpp"
#include <errno.h>
using namespace yb;
static logger::loglevel loglev=lev::TRACE;
__thread char errbuf[512];
thread_local std::string times;
__thread time_t lastime;
__thread pid_t tid;
const char *strerror_mr(int err)
{
    return strerror_r(err, errbuf, sizeof(errbuf));
}
const char *LogLevelStr[logger::NUM_LOG_LEVELS] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL",
};
void dafaultoutput(const char *msg, int len)
{
    fwrite(msg, 1, len, stdout);
}
void dafaultflush()
{
    fflush(stdout);
}
logger::OutputFunc g_output = dafaultoutput;
logger::FlushFunc g_flush = dafaultflush;
logger::logger(sourcefile file_, int line_, const char *func_, int logerrno, loglevel level_) : time(Timestamp::now()), basename(file_), line(line_), func(func_),
                                                                                                errnos(logerrno)
{
    setLogLevel(level_);
    formatTime();
    Showerr(errno,func);
    streams << (tid ? tid : (tid = getid())) << " " << LogLevelStr[level] << " ";
    streams << strerror_mr(errnos) << yb::endl;
}
logger::~logger()
{
    streams << " - " << basename.data << ':' << line << yb::endl;
    const logstream::logbuf &buffer(streams.getBuf());
    g_output(buffer.begin(), buffer.sizes());
    if (level == loglevel::FATAL)
    {
        g_flush();
        abort();
    }
}
void logger::formatTime()
{
    time_t misecond = time.secondsSinceEpoch();
    if (misecond != lastime)
    {
        lastime = misecond;
        times = std::move(time.toFormattedString(true));
    }
    streams << times << " ";
}
void logger::setLogLevel(loglevel level_)
{
    loglev = level_;
}
void logger::setOutput(OutputFunc t)
{
    g_output = t;
}
void logger::setFlush(FlushFunc t)
{
    g_flush = t;
}