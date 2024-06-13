# 3.5.3 指针和数组
尽管能计算得到尾后指针，但这种操作用法极易出错。为了 让指针的使用更为简单，更安全，C++ 11 标准库应用了两个名为begin和end 的函数。（P106）
标准库函数 begin 和end 


# 6.3.3 返回数组指针
因为数组不能被拷贝，所以函数不能返回数组。
返回数组指针的函数形式如下:

Type (*function(parameter_list))[dimension]
auto func(int i)-> int(*)[10];


具体点的例子:
int(*func(int i))[10];

typedef int arr_int[10];

using int arr_int[10];

arr_int* func(int i);


# 6.4 函数重载
const_cast 在重载函数的情景中最有用。（P209）
# 6.5.1 默认实惨
局部变量不能做为默认实惨。
# 6.5.2 内联函数和 constexpr 函数 放在头文件内，内联函数和constexpr 函数可以在程序中多次定义（P215）
# 6.5.3 调试帮助
- assert 预处理红 在头文件 cassert 头文件中，assert 依赖于一个名为NDEBUG 预处理宏.除了用于assert外，NDEBUG编写自己的条件调试代码
__func__ 函数名字符串值
__FILE__ 文件名字符串值
__LINE__ 行号字符串值
__TIME__ 编译时间字符串值
__DATE__ 编译日期字符串值

# 6.7函数指针 (是类型)
想要声明一个指向函数的指针，只需要用指针替换函数名即可
具体的例子如下：
bool lengthCompare(const string &,const string&);
该函数的类型为
bool(const string &,const string&)
该函数的指针类型为
bool(*pf)(const string &,const string&)
返回函数指针的应用场景：
1、动态绑定
2、函数的参数（函数指针为参数）
# 注意事项
返回值：
不能返回局部变量的引用和指针，
不能返回数组和函数
# 7.1.5拷贝，赋值和析构，
对象在几种情况下会被拷贝：
1、变量初始化
2、以值的方式传递参数或返回对象，

使用赋值运算符

# 7.5.4 隐式的类类型转换 
# 8.1 IO类
使用IO操作处理string中的字符会很方便。
# 8.1.2 条件状态
由于流可能处于错误状态，因此代码通常应该在使用一个流之前检查它是否处于良好状态，确定一个流对象的状态的最简单方式是将它作为一个条件来使用
``` c++ 
while( cin>>word)
    //ok 读取操作成功
```
# 9.1 顺序容器

vector 可变大小数组
使用范例：
声明方式：
```cpp
vector<int> vec;    // 0
vector<int> vec(10);    // 0
vector<int> vec(10,1);  // 1
vector<int> vec{1,2,3,4,5}; // 1,2,3,4,5
vector<int> vec(other_vec); // same as other_vec
vector<int> vec(other_vec.begin(), other_vec.end()); // same as other_vec

```
删除出元素范例
```cpp
#include<forward_list>
#include<list>
//list
list<int> lst={0,1,2,3,4,5,6,7,8,9,0};
auto it=lst.begin();
while(it!=lst.end()){
    if(*it%2)
    {
        it=lst.erase(it);//删除该元素
    }else{
        ++it;
    }
}
//forward_list单向链表 P313
forward_list<int> flst={0,1,2,3,4,5,6,7,8,9}
auto prev=flst.before_begin();//首前元素
auto curr=flst.begin();//首元素
while(curr!=flst.end()){//仍有元素需要处理
    if(*curr%2){
        curr=flat.erase_after(prev);//删除并移动curr
    }else{
        prev=curr;//prev指向curr之前的元素
        ++curr;//移动迭代器curr, 指向下一个元素
    }
}
```

# 9.2 容器库概览
对容器可以保存的元素类型的限制。
没有默认构造函数的类类型容器的声明
```c++
std::vector<noDefault> v1(10,init);//init 为函数指针，为元素初始化器。
```
# 9.2.1 迭代器
使用左闭合范围蕴含的编程假定：1、如果begin与end 相等，则范围为空
2、如果begin与end 不等，则范围至少包含一个元素，且begin指向该范围中的第一个元素
3、我们可以对begin 递增若干次，使得begin==end
迭代器比较范例
```cpp
list<int> lst1{10,12};
list<int>::iterator begin = lst1.begin(), end = lst1.end();
while (begin != end){//迭代器比较
    *begin=val;//范围非空，因此begin指向第一个元素
    ++begin;//移动迭代器，获取下一个元素
}


```

# 9.3.2 访问元素
在解引用一个迭代器或调用front 或back  之前检查是否有元素,访问成员函数返回的是引用。在容器中访问元素的成员函数（即 front, back,下标和at）返回的都是引用，但是接受返回值的变量必须声明为引用类型。
```cpp
if(!c.empoty()){
    c.front()=42;//将42 赋予C中的第一个元素
    auto & v=c.back();//获得指向最后一个元素的引用
    v=1024;//改变C 中的元素
    auto v2=c.back();//v2不是一个引用，它是c.back()的一个拷贝
    v2=0;//未改变C中的元素
}
```



# 14.9.1 类型转换运算符 ————类型转换运算符是类的一种特殊成员函数，
operator type()const;
因为类型转换运算符是隐式执行的，所以无法给这些函数转递实参，也就不能在类型转换运算符的定义中使用任何形参。


# 关键字
explicit 抑制构造函数定义的隐式类型转换。

# 类型别名 typdef 、using


# 类

需要控制如何初始化，
需要控制拷贝
需要控制赋值
需要控制销毁
------ 需要考虑使用场景
静态成员函数，静态成员变量，单例时需要
# 构造函数
特点：
不能有返回值
explicit 构造函数只能用于直接初始化；（P265）
constexpr 构造函数（P267）
# const 成员函数声明

int func(string s)const 

constexpr 函数的要求 唯一可执行语句就是返回语句。也可以是空语句，

虚表指针，虚函数，纯虚函数，虚函数指针。

# 模板 ————C++语言既有类模板也有函数模板，模板本身不是类也不是函数，相反可以看作为编译器生成类或函数编写的一份说明，
编译器根据模板来创建类或函数的过程称为实例化，当使用模板时需要指出，编译器应把类模板或函数模板实例化成何种类型或函数。
利用模板，我们可以使用具有继承关系的类，而不必了解继承机制的工作细节。