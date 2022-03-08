#include "logfile.hpp"
using namespace yb;
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
void logfile::flush()
{
    if (mutex_)
    {
        std::lock_guard<std::mutex> t(*mutex_);
        file->flush();
    }
    else
    {
        file->flush();
    }
}
void logfile::append(const char *log, int len)
{
    if (mutex_)
    {
        std::lock_guard<std::mutex> t(*mutex_);
        unlock_append(log, len);
    }
    else
    {
        unlock_append(log, len);
    }
}
void logfile::unlock_append(const char *log, int len)
{
    file->append(log, len);
    if (file->writebyte() > rollsize)
    {
        rollfile();
    }
    else
    {
        ++count;
        if (count > checkevery)
        {
            count = 0;
            time_t now = time(NULL);
            time_t thisday = now - (now % daylight);
            if (thisday != lastday)
            {
                rollfile();
            }
            else if (now - lastflush > flushtime)
            {
                lastflush = now;
                flush();
            }
        }
    }
}
