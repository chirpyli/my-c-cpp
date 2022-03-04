/* #include study examples */
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstring>

#include "print.c"


/*
 * C 常见内存错误。

*/
// 堆溢出示例
void malloc_test()
{
    char* t1 = (char*) malloc(100);
    char* t2 = (char*) malloc(6);
    const char* str = "this is a test";
    memcpy(t2, str, strlen(str));       // 超过内存分配空间，但是不报错，可运行，可能会引起未知问题，

    print(t2);

    free(t1);
    free(t2);
}
/*
[postgres@slpc C]$ g++ -fsanitize=address -g main.c 
[postgres@slpc C]$ ./a.out 
=================================================================
==32817== ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60040000dffd at pc 0x400c91 bp 0x7ffdbc8a7b20 sp 0x7ffdbc8a7b10
WRITE of size 1 at 0x60040000dffd thread T0

*/

// 栈溢出示例
void stack_overflow_test()
{
    int test[10];
    test[1] = 0;
    test[11] = 1;   // 越界 ，可以正常编译，运行时出错。
    int a = test[12];  // 越界 
    printf("%d", a);
}
/*
[postgres@slpc C]$ g++ -fsanitize=address -g main.c 
[postgres@slpc C]$ ./a.out 
=================================================================
==32774== ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffc4618cefc at pc 0x400d9a bp 0x7ffc4618ce90 sp 0x7ffc4618ce80
WRITE of size 4 at 0x7ffc4618cefc thread T0

*/

// 全局内存溢出
int global_data[10] = {0};
void global_memory_overflow_test()
{
    int data = global_data[10];
    printf("%d", data);
}
/*
[postgres@slpc C]$ g++ -fsanitize=address -g main.c 
[postgres@slpc C]$ ./a.out 
=================================================================
==32593== ERROR: AddressSanitizer: global-buffer-overflow on address 0x000000602228 at pc 0x400e54 bp 0x7ffdd9bf3960 sp 0x7ffdd9bf3950
READ of size 4 at 0x000000602228 thread T0

*/

// 内存释放后继续使用
void use_memory_after_free_test()
{
    char *test = new char[10];
    strcpy(test, "test");
    delete []test;
    print(test);
    char c = test[0];
}
/*
[postgres@slpc C]$ g++ -fsanitize=address -g main.c 
[postgres@slpc C]$ ./a.out 
test   可输出但是危险，因为实际情况是中间可能会有其他代码使用改内存，此时如果print是修改了改内存的话，会很危险
=================================================================
==33257== ERROR: AddressSanitizer: heap-use-after-free on address 0x60040000dff0 at pc 0x401054 bp 0x7ffffd1c94b0 sp 0x7ffffd1c94a0
READ of size 1 at 0x60040000dff0 thread T0

*/


int main() {

    // malloc_test();

    // stack_overflow_test();

    // global_memory_overflow_test();
    
    use_memory_after_free_test();

    return 0;
}


// g++ -fsanitize=address -g main.c 可查看到出现的内存问题