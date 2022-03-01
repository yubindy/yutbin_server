#ifndef LOGFILE_H
#define LOGFILE_H
#include "nocopy.h"
#include <memory>
#include <mutex>
#include <string>
#include <ctime>
#include "fileutil.h"
#include "Timestamp.h"
namespace yb
{
    class fileadd; //日志写入类
    class logfile : nocopy
    {
    public:
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
}
#endif
