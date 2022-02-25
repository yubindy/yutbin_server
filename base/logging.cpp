#include "logging.h"
#include "Thread.cpp"
#include <errno.h>
using namespace yb;
logger::loglevel loglev;
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
logger::logger(sourcefile file_, int line_, const char *func_, int logerrno, loglevel level_) : time(Timestamp::now()), basename(file_), line(line_), func(func_),
                                                                                                errnos(logerrno)
{
    setLogLevel(level_);
    formatTime();
    streams << (tid ? tid : (tid = getid())) << " " << LogLevelname[level] << " ";
    streams<< strerror_tl(errnos) <<yb::endl;
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