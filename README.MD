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
使用IO操作处理string中的字符会很方便。（P278） 此话怎讲？

IO类型间的关系


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

# 9.2.5 赋值和swap （P302）（不适用于关联容器和array）
使用assign（仅顺序容器）
与赋值运算符的区别：
1、赋值运算符要求 左边和右边的运算对象具有相同的类型。它将右边运算对象中所有元素拷贝到左边运算对象。中。
2、assign 允许我们从一个不同但相容的类型赋值，或者从容器的一个字序列赋值。
```cpp

list< string> names;
vector<const char*> oldStyle;
names=oldStyle;//错误，容器类型不匹配
names.assign(oldStyle.cbeing(),oldStyle.cend());//可以 将 const char* 转换为 string
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
# 使用迭代器需要考虑的问题：
1、编写改变容器的循环程序，添加/删除 vector 、string、deque 元素的循环程序必须考虑迭代器，引用和指针可能失效的问题。（P316）
2、不要保存end返回的迭代器


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

# 10 泛型算法 （排序和搜索...） 
算法是如何工作的（P337）
迭代器令算法不依赖于容器，但是依赖于元素类型的操作（P337）
除了少数例外，标准库算法都对一个范围内的元素进行操作，我们将此范围称为“输入范围”，接受输入范围的算法总是使用前两个参数来表示此范围，两个参数分别指向要处理的第一个元素和尾元素之后的位置的迭代器。虽然大多数算法遍历输入范围的方式相似，但它们使用范围中元素的方式不同，理解算法的最基本的方法就是了解它们是否读取元素，改变元素，或重排元素顺序。

# 10.2.1 只读算法
 一些算法只会读取其输入范围内的元素，而不改变元素，
 ```cpp
 #include <algorithm>
//如果在vec 中找到了想要的元素，则返回结果给指向它，否则返回结果为vec.cend()
auto result= std::find(vec.cbegin(),vec.cend(),val);
//在 ls 中统计 字符串“aa” 出现的次数
 std::count(ls.cbegin(), ls.cend(), "aa")
 //对vec 中的元素求和,和的初始值是0
 int sum= std::accumulate(vec.cbegin(),vec.cend(),0) 

```
##[Exercise 10.1 and 10.2](/CppPrimer-master/ch10/ex10_01_02.cpp)

# 操作两个序列的算法
另一个只读算法是equal,用于确定两个序列是否保存了相同的值。

```cpp
//roster2 中的元素数目应该至少与roster1一样多
bool isEqual=std::equal(roster1.cbegin(),roster1.cend(),roster2.cbegin())
```

# 10.2.2 写容器元素的算法
必须注意确保序列原大小至少不小于我们要求算法写入的元素数目。算法不会执行扩容操作。因此它们自身不可能改变容器的大小。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector; using std::cout; using std::endl; using std::fill_n; using std::fill;

int main()
{
    vector<int> vec{0,1,2,3,4,5,6,7,8,9};
    //将每个元素重置为0
    fill(vec.begin(),vec.end(),0);
    //将容器的一个子序列重置为1
    fill(vec.begin(),vec.begin()+vec.size()/2,1);
    //所有元素重置为0
    fill_n(vec.begin(), vec.size(), 0);
    
    for (auto i : vec)
        cout << i << " ";
    cout << endl;
}


```
# 介绍back_inserter (P341)
插入迭代器是一种向容器中添加元素的迭代器。back_inserter 它是定义在头文件iterator中的一个函数， back_inserter 接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。

# 拷贝算法 copy 传递给copy 的目的序列至少要包含与输入序列一样多的元素，
```cpp
int a1[]={0,1,2,3,4,5,6,7,8,9};
int a2[sizeof(a1)/sizeof(*a1)];//a2与a1 大小一样
//ret 恰好指向拷贝到a2的尾元素之后的位置
auto ret=std::copy(begin(a1),end(a1),a2);

//将所有值为0的元素修改为42，
replace(ilst.being(),ilst.end(),0,42);
//ivec 包含ilst的一份拷贝，0  不过原来在ilst中值为0的元素在ivec中 都被修改为42
replace_copy(ilst.being(),ilst.end(),back_inserter(ivec),0,42)

```

# 10.2.3 重排容器元素的算法


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

# 模板 ————C++语言既有类模板也有函数模板 其中vector 是一个类模板，模板本身不是类也不是函数，相反可以看作为编译器生成类或函数编写的一份说明，
编译器根据模板来创建类或函数的过程称为实例化，当使用模板时需要指出编译器应把类模板或函数模板实例化成何种类型或函数。
