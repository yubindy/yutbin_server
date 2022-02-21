#ifndef LOGFILE.H
#define LOGFILE .H
#include "nocopy.h"
#include <memory>
#include <mutex>
#include <string>
#include <ctime>
#include "fileutil.h"
#include "Timestamp.h"
using namespace yb;
class fileadd;  //日志写入类
class logfile : nocopy
{
    logfile(const std::string &name_, off_t rollsize_, bool threadsafe_ = true, int flushtime_ = 3, int checkevery_ = 1024) : name(name_), rollsize(rollsize_), threadsafe(threadsafe_), flushtime(flushtime_), checkevery(checkevery_), count(0), mutex_(threadsafe ? new std::mutex : nullptr),
                                                                                                                              lastday(0), lastroll(0), lastflush(0) { rollfile(); }
    ~logfile();
    void append(const char *log, int len);
    void flush();
    bool rollfile();
    std::string addtime(const std::string filename, time_t *t);

private:
    void unlock_append(const char *log, int len);
    const std::string name;
    const off_t rollsize;
    const bool threadsafe;
    const int flushtime;
    const int checkevery;
    int count;
    std::unique_ptr<std::mutex> mutex_;
    time_t lastday;
    time_t lastroll;
    time_t lastflush;
    std::unique_ptr<fileadd> file;
    const static int daysecond = 60 * 60 * 24;
};
bool logfile::rollfile()
{
    time_t now(0);
    std::string filename(name);
    filename = logfile::addtime(filename, &now);
    time_t nowday = now - (now % daylight);
    if (now < lastroll)
    {
        lastroll = now;
        lastflush = now;
        lastday = nowday;
        file.reset(new fileadd(filename));
        return true;
    }
    return false;
}
std::string logfile::addtime(std::string filename, time_t *t)
{
    *t = time(NULL);
    Timestamp tap(*t);
    return filename + tap.toFormattedString(true) + ".log";
}
void logfile::append(const char *log, int len)
{
    if (threadsafe)
    {
        std::lock_guard<std::mutex> t(*mutex_);
        unlock_append(log, len);
    }
    else
    {
        unlock_append(log, len);
    }
}
void LogFile::append_unlocked(const char* logline, int len)
{
    file->append();
}
#endif
