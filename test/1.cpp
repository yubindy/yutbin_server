#include<functional>
#include<stdio.h>
using Funtor=std::function<void()>;
void fun(int t)
{
    printf("%d",t);
}
void doing(int x)
{
    auto s=std::bind(fun,std::placeholders::_1);
    return s(x);
}
int main()
{
    doing(8);
}