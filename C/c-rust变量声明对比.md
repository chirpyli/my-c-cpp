
### C与Rust对比之变量声明
Rust与C语言有很多的不同，在变量声明方面，Rust更“安全”一些。C声明变量可以不进行初始化，编译器也不进行是否有初试化的检查，但Rust会进行严格的检查，如果声明变量未初始化则编译报错。这可以防止程序员因未进行变量初始化造成的BUG。

在C语言中可以可以声明一个变量，不进行初试化就可以使用，编译器不会报错，但可能会导致运行时的异常行为。比如：
```c++
#include<stdio.h>
#include <stdbool.h>

bool is_post(int data) {
    return data > 0;
}

int main() {

    bool var;
    /* 假设中间有很多代码 */
    int data = 10;
    if (data != 10) 
    {
        var = is_post(data);
    }
    /* 假设中间有很多代码*/

    // 有可能出现变量没有声明就使用的情况
    if (var)
        printf("maybe error here.\n");
    else 
        printf("maybe not you want.\n");

    return 0;
}
```
声明的时候没有初始化，必须确保后面使用前被赋值，否则的话可能会造成运行结果的错误或者其他莫名奇妙的问题。当工程很大的时候排查BUG会比较难排查。

对Rust，变量声明的时候必须初始化，否则的话编译器这关就过不去，所以就不会踩这个坑了。
```rust
fn main() {
    let a;
    if a > 1 {
        a = 10;
    }
}
```
编译`cargo build`：
```rust
error[E0381]: use of possibly-uninitialized variable: `a`
 --> src/main.rs:4:8
  |
4 |     if a > 1 {
  |        ^ use of possibly-uninitialized `a`

For more information about this error, try `rustc --explain E0381`.
error: could not compile `playground` due to previous error
```
