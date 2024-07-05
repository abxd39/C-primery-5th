P545 页
有时我们需要改变派生类继承的某个名字的访问级别，通过using 声明 可以达到这一目的
```cpp
class Base{
    public:
    std::size_t size()const{
        retun n;
    }
    protected:
    std::size_t n;
};

class Derive:priavte Base{
    public:
    //保持对象尺寸相关的成员的访问级别
    using Base::size;
    priavte:

    using Base::n;
}

```
因为Dervied  使用了私有继承，所以继承而来的成员 size和n(默认情况下)是Derived的私有成员。