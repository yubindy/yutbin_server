#include<functional>
#include<stdio.h>
void func(int& t)
{
    printf("左\n");
}
void func(int&& t)
{
    printf("右值\n");
}
int main()
{
    int t=20;
    func(t);
    func(std::move(std::move(t)));
}