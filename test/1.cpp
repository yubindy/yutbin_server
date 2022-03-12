#include <functional>
#include <stdio.h>
#include <string.h>
int main()
{
    char buf[50] = "csfcsdc\r\ndcdscfdvfd";
    int pt=0,len=50;
    while (pt != len && buf[pt++] != '\r' && buf[pt] != '\n')
    {
    }
    printf("%d:%s",pt,buf+pt);
}