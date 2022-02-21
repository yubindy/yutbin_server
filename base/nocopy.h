#ifndef NOCOPY_H
#define NOCOPY_H
using namespace yb;
class nocopy
{
public:
    nocopy(const nocopy &) = delete;
    nocopy operator=(const nocopy &) = delete;
    nocopy() = default;
    ~nocopy() = default;
};

#endif
