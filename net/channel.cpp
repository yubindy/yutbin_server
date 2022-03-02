#include"channel.h"
using namespace yb;
using namespace yb::net;
void channel::setreadback(readback t)
{
    rb=std::move(t);
}
