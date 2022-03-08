#include "netbuffer.hpp"
#include <errno.h>
#include <sys/uio.h>
using namespace yb::net;
ssize_t netbuffer::readfd(int fd, int *err)//减少文件读写，只读一次
{
    char externbuf[65536];
    struct iovec vec[2];
    const size_t writable=writebyte();
    vec[0].iov_base=begin()+writeindex_;
    vec[0].iov_len=writable;
    vec[1].iov_base=externbuf;
    vec[1].iov_len=sizeof(externbuf);
    size_t n=readv(fd,vec,2);
    if(n<0)
    {
        *err=errno;
    }else if(n<=writable)
    {
        writeindex_+=n;
    }else
    {
        writeindex_=buffer_.size();
        append(externbuf,n-writable);
    }
    return n;
}