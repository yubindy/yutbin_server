#ifndef ASYNCLOGGING_H
#define ASYNCLOGGING_H
#include "logging.h"
#include "logfile.h"
#include "nocopy.h"
#include <vector>
#include <atomic>
#include <future>
namespace yb
{
  class AsyncLogging : nocopy
  {
  public:
    AsyncLogging(const std::string &basename,
                 off_t rollSize,
                 size_t flushInterval = 3);

    ~AsyncLogging();
    void append(const char *logline, int len);
    void start();
    void stop();

  private:
    void threadFunc();
    using buffer = logbuffer<logsmallbuffer>;
    using bufptr = std::unique_ptr<logbuffer<logsmallbuffer>>;
    using bufvector = std::vector<bufptr>;

  private:
    std::thread td_;
    mutable std::mutex m_;
    std::condition_variable cv_;
    std::promise<void> p_;
    std::atomic<bool> running_;
    size_t roll_size_;
    const size_t flushInterval_;
    size_t writeInterval_;
    bufptr cur_;
    bufptr prv_;
    bufvector tranbufvector;
    std::string logFileName_;
  };
}
#endif
