/*
 * 缓冲区溢出漏洞示例
 */
#include<stdio.h>

void hello()
{
    fprintf(stderr, "hello!\n");
}

void func()
{
    void *buf[10];
    static int i;
    
    for (i = 0; i < 100; i++)
    {
        buf[i] = hello;
    }
}

void main()
{
    int buf[1000];
    buf[999] = 10;

    func();

    return 0;
}