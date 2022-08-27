#include "../../include/fileutil.hpp"
#include"../../include/logging.hpp"
//对文件操作的封装
using namespace yb;
fileadd::fileadd(std::string filename) : file(fopen(filename.c_str(), "ae")), writed(0)
{
    assert(file);
    setbuf(file, buf); //设置为用户态缓冲
}
size_t fileadd::write(const char *logline, size_t len)
{
    return fwrite_unlocked(logline, 1, len, file);
}
void fileadd::flush()
{
    fflush(file);
}
size_t fileadd::append(const char *logline, size_t len)
{
    int writes = 0, remain = len;
    int t = 0;
    int err;
    while (writes != len)
    {
        t = write(logline + writes, remain);
        if (t != remain)
        {
            if (err=ferror(file))
            {
                fprintf(stderr,"fileadd::append failed %s",strerror_mr(err));
            }
        }
        writes += t;
        remain -= t;
    }
    writed += writes;
    return writes;
}