struct 与class 关键字唯一的区别是默认成员访问说明符及默认派生类访问说明符，除此之外再无其他不同。
```cpp
class Base{
    size_t m;//默认private
    /**/
    };
struct D :Base{
    size_t m;//默认public
    /**/
    };//默认public继承
class Derived:Base{/**/};//默认private继承
```