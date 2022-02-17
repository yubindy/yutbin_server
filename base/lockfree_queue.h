#include <atomic>
#include <memory>
namespace yb{
template <typename T>
class lf_queue //无锁队列实现
{
public:
    class node
    {
        std::shared_ptr<T> val;
        node *next;
    };
    lf_queue();
    lf_queue(const lf_queue &t) = delete;
    lf_queue operator=(const lf_queue &t) = delete;
    ~lf_queue();
    void push(T &&num);
    std::shared_ptr<T> pop();
private:
    std::atomic<node *> front;
    std::atomic<node *> end;
};
}