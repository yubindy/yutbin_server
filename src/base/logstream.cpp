#include "../../include/logstream.hpp"
using namespace yb;
logstream &endl(logstream &stream)
{
    if (stream.getBuf().avail() >= 1)
    {
        stream.getBuf().append('\n');
    }
    return stream;
}
template <typename T>
void logstream::formatint(T v)
{
    auto s = std::to_string(v);
    auto len = s.size();
    if (len <= buf_.avail())
        buf_.append(s, len);
}
logstream &logstream::operator<<(short v)
{
    return *this << static_cast<int>(v);
}
logstream &logstream::operator<<(unsigned short v)
{
    return *this << static_cast<unsigned int>(v);
}
logstream &logstream::operator<<(int v)
{
    formatint(v);
    return *this;
}
logstream &logstream::operator<<(unsigned int v)
{
    formatint(v);
    return *this;
}
logstream &logstream::operator<<(long v)
{
    formatint(v);
    return *this;
}
logstream &logstream::operator<<(unsigned long v)
{
    formatint(v);
    return *this;
}

logstream &logstream::operator<<(long long v)
{
    formatint(v);
    return *this;
}

logstream &logstream::operator<<(unsigned long long v)
{
    formatint(v);
    return *this;
}

logstream &logstream::operator<<(const void *v)
{
    if (32 <= buf_.avail())
    {
        int len = snprintf(buf_.stringend(), 32, "%p", v);
        buf_.addlen(len);
    }
    return *this;
}
logstream &logstream::operator<<(float v)
{
    return *this << static_cast<double>(v);
    return *this;
}
logstream &logstream::operator<<(double v)
{
    if (32 <= buf_.avail())
    {
        int len = snprintf(buf_.stringend(), 32, "%p", v);
        buf_.addlen(len);
    }
    return *this;
}
