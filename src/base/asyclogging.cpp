#include "asynclogging.hpp"
#include<iostream>
#include <assert.h>
using namespace yb;
AsyncLogging::AsyncLogging(const std::string &basename,
                           off_t rollsize,
                           size_t flushs) : td_(std::bind(&AsyncLogging::threadFunc, this), "loggging"), roll_size_(rollsize),
                                            flushInterval_(flushs), cur_(new buffer), prv_(new buffer)
{
    cur_->reset();
    prv_.reset();
    tranbufvector.reserve(16);
}
AsyncLogging::~AsyncLogging()
{
    running_ = false;
    cv_.notify_one();
    td_.join();
}
void AsyncLogging::append(const char *logline, int len) //发送端
{
    if (!running_)
    {
        return;
    }
    std::lock_guard<std::mutex> lock(m_);
    if (cur_->avail() > len)
    {
        cur_->append(logline, len);
    }
    else
    {
        tranbufvector.push_back(std::move(cur_));
        if (prv_)
        {
            prv_ = std::move(prv_);
        }
        else
        {
            cur_.reset(new buffer);
        }
        cur_->append(logline, len);
        cv_.notify_all();
    }
}
void AsyncLogging::start()
{
    running_.store(true);
    std::future<void> fut = p_.get_future();
    fut.get();  //阻塞到进入循环
}
void AsyncLogging::threadFunc() //接收端
{
    bufptr buf1(new buffer);
    bufptr buf2(new buffer);
    logfile file(logFileName_, roll_size_, flushInterval_);
    bufvector recvvector;
    logger::setFlush(std::bind(&logfile::flush, &file));
    logger::setOutput(std::bind(&logfile::append, &file, std::placeholders::_1, std::placeholders::_2));
    p_.set_value();
    while (running_.load())
    {
        {
            std::unique_lock<std::mutex> mut(m_);
            while (tranbufvector.empty())
            {
                cv_.wait_for(mut, std::chrono::seconds(flushInterval_));
            }
            tranbufvector.push_back(std::move(cur_));
            cur_ = std::move(buf1);
            if (!prv_)
            {
                prv_ = std::move(buf2);
            }
            recvvector.swap(tranbufvector);
        }
        if (recvvector.size() > 25)
        {
            char buferr[256];
            snprintf(buferr, sizeof buferr,
                     "Dropped log messages at %s, %lu larger buffers\n",
                     Timestamp::now().toFormattedString(true).c_str(),
                     recvvector.size() - 2);
            fputs(buferr, stderr);
            recvvector.resize(2);
        }
        for (auto &buf : recvvector)
        {
            file.append(buf->begin(), buf->sizes());
        }
        if (recvvector.size() > 2)
        {
            recvvector.resize(2);
            if (!buf1)
            {
                buf1 = std::move(recvvector.back());
                recvvector.pop_back();
                buf1->reset();
            }
            if (!buf2)
            {
                buf2 = std::move(recvvector.back());
                recvvector.pop_back();
                buf1->reset();
            }
        }
        recvvector.clear();
        file.flush();
    }
    file.flush();
}

