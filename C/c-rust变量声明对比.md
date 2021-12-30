
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

### 可变性
在Rust中变量默认是不可变的，如`let a = 10`。如果要声明一个可变变量需要加`mut` ，如`let mut a = 10`。而在C语言中则不是，你可以随意修改变量，除非加了`const`声明是常量。谈起Rust，就会有一个词“安全”。Rust不仅仅是强调内存安全，其他方面也处处体现出其设计思想。对默认不可变，无论其出发点是什么，实际工程上，默认不可变确实更不容易犯错。如果默认不可变，那么一旦尝试修改，编译器可以在编译期发现，避免了默认可变情况下容易犯的错误。比如我们在写C函数时，总会有如下的习惯：
```c++
int func(const char *name, const int value)
{
    ......
}
```
这样做的好处一方面可以避免函数内部误修改参数内容，在编译阶段就可以发现错误，另一方面给其他阅读代码的人以方便，立马就知道这个参数不会在函数内部被修改。这无疑是个较好的编程习惯。在Rust中，默认不可变，只有在可变是会`mut`，这样也有类似的好处，一方面避免了可能误修改不可变变量的发生，另一方面在阅读代码上无疑是更容易理解的，尤其是阅读别人写的大量代码的时候。有点最佳工程实践的味道。当工程代码量很大的时候，逻辑方面的错误很容易定位发现，往往是这种不起眼的小细节引发的BUG更难定位。

