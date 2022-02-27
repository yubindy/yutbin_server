#include "asynclogging.h"
using namespace yb;
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
AsyncLogging::AsyncLogging(const std::string &basename,
                           off_t rollSize,
                           int flushInterval = 3):td(std::bind(AsyncLogging::threadFunc,this),"logging"),roll_size_(rollSize),flushInterval_(flushInterval),
                           writeInterval_()
{

}
