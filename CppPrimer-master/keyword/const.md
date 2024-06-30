
C++ 函数参数列表后面的const 修饰的函数，此const的作用?

在C++中，函数参数列表后面的`const`用来修饰成员函数，这个`const`的作用是表明该成员函数不会修改对象的状态，也就是说在这个函数内不能修改类的成员变量。

举个例子：
```cpp
class MyClass {
public:
    int getValue() const { // 这个const表明getValue函数不会修改对象的状态
        return value;
    }

    void setValue(int val) {
        value = val;
    }

private:
    int value;
};
```

在上面的例子中，`getValue`函数在参数列表后面加了一个`const`，因此它承诺不会修改类的成员变量`value`。编译器会在编译时进行检查，在这个函数内部，如果尝试修改任何成员变量或者调用非`const`成员函数，就会报错。

这是对函数行为的一种保证，有助于编写更加可靠和易于维护的代码。