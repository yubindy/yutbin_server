#include "../base/asynclogging.h"
#include"../base/logfile.h"
#include <unistd.h>
using namespace yb;
std::unique_ptr<logfile> g_logFile;

void outputFunc(const char* msg, int len)
{
  g_logFile->append(msg, len);
}

void flushFunc()
{
  g_logFile->flush();
}

int main(int argc, char* argv[])
{
   char name[256] = { 0 }; 
  strncpy(name, argv[0], sizeof name - 1);
  printf("%s",name);
  g_logFile.reset(new logfile(::basename(name), 200*1000));
  logger::setOutput(outputFunc);
  logger::setFlush(flushFunc); 
  std::string line = "1234567890 abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

  for (int i = 0; i < 10000; ++i)
  {
    LOG(logger::INFO)<<line<<endl;
    usleep(1000);
  } 
}
