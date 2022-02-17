#include <mutex>
#include<functional>
class lf_queue;
class threadpool
{
private:
    typedef std::function<void()> task;
    lf_queue *que;
    std::unique_lock<std::mutex> mut;
    std::conditional<yes,

public:
};
int main()
{
}