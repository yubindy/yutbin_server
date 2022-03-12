#include"debug.hpp"
std::string debug::get_string()
{
   printf("%s",t.data());
}
void debug::push_int()
{
    for(int i=0;i<10;i++)
    {
        num.emplace_back(val);
    }
    for(int i=0;i<10;i++)
    printf("%d",i);
}
int main()
{
    debug t(1,"wo fu l\n");
    t.push_int();
    t.get_string();
    return 0;
}