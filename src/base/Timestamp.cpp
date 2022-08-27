#include "../../include/Timestamp.hpp"
#include <chrono>
using namespace yb;

std::string Timestamp::toString() const
{
    char buf[32] = {0};
    time_t a = time % ktime;
    time_t b = time / ktime;
    snprintf(buf, sizeof(buf), "%ld:%ld", a, b);
    return buf;
}
std::string Timestamp::toFormattedString(bool showtosecond) const
{
    char buf[64] = {0};
    struct tm time_;
    time_t a = static_cast<time_t>(time % ktime);
    time_t b = time / ktime;
    gmtime_r(&a, &time_);
    if (showtosecond)
    {
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
                 time_.tm_year + 1900, time_.tm_mon + 1, time_.tm_mday,
                 time_.tm_hour, time_.tm_min, time_.tm_sec,
                 time);
    }
    else
    {
        snprintf(buf, sizeof(buf), "%4d%02d%02d ",
                 time_.tm_year + 1900, time_.tm_mon + 1, time_.tm_mday);
    }
    return buf;
}
Timestamp Timestamp::now()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return Timestamp(tv.tv_sec*Timestamp::ktime+tv.tv_usec);
}
