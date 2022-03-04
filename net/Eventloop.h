#ifndef EVENTLOOP_h
#define EVENTLOOP_h
#include <vector>
#include<../base/nocopy.h>
namespace yb
{
    namespace net
    {
        class Eventloop:
        {
        public:
            void assertinloop();
        private:
        };
    }
}
#endif