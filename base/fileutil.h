#include <fcntl.h>
#include <string.h>
#include<string>
#include <assert.h>
#include<stdio.h>
#include<errno.h>
namespace yb
{
    class fileadd //处理文件写入的资源类
    {
    public:
        fileadd(const std::string filname);
        ~fileadd() { fclose(file); }
        size_t append(const char *logline, size_t len);
        void flush();
        off_t writebyte() { return writed; }
        size_t write(const char *logline, size_t len);

    private:
        off_t writed;
        FILE *file;
        char buf[64 * 1024];
    };
}