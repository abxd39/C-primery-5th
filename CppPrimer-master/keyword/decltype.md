***decltype 类型指示符 *** p63
有时会遇到这种情况：希望从表达式的类型推断出要定义的变量类型，但是不想用该表达式的初始化变量。C++11 引入decltype 关键字
例如：
```cpp
decltype(f())  sum =x://sum的类型就是函数f的返回类型。

const int ci=0,&cj=ci;
decltype(cj) x=0;//x的类型是 const int
decltype(cj) j=x;//y 的类型是 const int& ,y 绑定到变量x
decltype(cj) z;//错误 ：z 是一个引用类型，必须初始化。 
```
需要指出的是，引用从来都作为其所致对象的同义词出现，只有在 ***decltype*** 处是一个例外

decltype 和引用

```cpp
int i=42,*p=&i,&r=i;
decltype(r+0) b;//正确： 加法的结果是int  因此b是一个（未初始化的）int 
decltype (*p) c;//错误：c是int &类型 必须初始化

decltype ((i)) d;//错误：d 是int & 必须初始化

decltype(i) e;//正确：e是一个（未初始化的）int
```
***WARNING***
切记：decltype ((variable)) （双层括弧）的结果永远是引用，而decltype (variable) 结果只有当 variable 本身就是一个引用时才是引用。

