#include"logging.hpp"
#include <cmath>
using namespace yb;
int main(int argc, char const *argv[])
{ 
  logger::setLogLevel(lev::INFO);
  logger log("asd.log",20,nullptr,0);
  int t = 10000;
  const char *s = NULL;
  void *p = NULL;
  int *pp = &t;
  long long ll = 232354562143;
  logbuffer<logsmallbuffer> bf;
  bf.append("asad", 4);
  LOG(lev::INFO)<<"helo";
  log.streams << 1.0 << 2.12345432 << ll << std::string("pow:") << pow(2, 35)
         << "helo world\n"
         << p << bf << pp;
  auto &b = log.streams.getBuf();
  b.debugString();
  return 0;
}
//     void threadFunc();
//     std::thread td_;
//     mutable std::mutex m_; 
//     std::condition_variable cv_;
//     std::promise<void> p_;
//     std::atomic<bool> running_;
//     size_t roll_size_;
//     const size_t flushInterval_;
//     size_t writeInterval_;
//     bufptr cur_;
//     bufptr prv_;
//     bufvector transBufVec_;
//     std::string logFileName_;