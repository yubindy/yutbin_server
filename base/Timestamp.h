#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include "nocopy.h"
#include <sys/time.h>  
#include <unistd.h>
#include <boost/operators.hpp>
//具体为微秒
namespace yb{
class Timestamp : public boost::less_than_comparable1<Timestamp>
{
public:
    explicit Timestamp(time_t time_) : time(time_) {}
    Timestamp();
    ~Timestamp();
    std::string toString() const; 
    std::string toFormattedString(bool showtosecond) const;
    inline time_t get() const { return time; }
    void swap(Timestamp &pt, Timestamp &qt)
    {
        std::swap(pt, qt);
    }
    time_t secondsSinceEpoch()
    {
        return static_cast<time_t>(time / ktime);
    }
    static Timestamp now();
    
    static const int ktime = 1000 * 1000;

private:
    time_t time;
};
inline bool operator<(Timestamp pt, Timestamp qt)
{
    return pt.get() < qt.get();
}
inline bool operator==(Timestamp pt, Timestamp qt)
{
    return pt.get() == qt.get();
}
inline double timenum(Timestamp high, Timestamp low)
{
    return static_cast<double>((high.get() - low.get()) / Timestamp::ktime);
}
inline Timestamp addTime(Timestamp t, double f)
{
    time_t fk = static_cast<time_t>(f * Timestamp::ktime);
    return Timestamp(t.get() + fk);
}
}
#endif