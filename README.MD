
# 3.3 标准库类型 vector （P86）

# 3.4 迭代器介绍

# 3.5.4 C风格字符串
表3.8 C风格字符串函数（P109）

# 3.5.3 指针和数组
尽管能计算得到尾后指针，但这种操作用法极易出错。为了 让指针的使用更为简单，更安全，C++ 11 标准库应用了两个名为begin和end 的函数。（P106）
标准库函数 begin 和end 

# 6.2.6 含有不确定数量形参的函数 （P197）
省略号形参 一般只用于与C函数交换的接口程序。
initializer_list 形参 ，如果函数的实惨数量未知但是类型是相同的，
可变参数模板。

# initializer_list 形参  initializer_list 是一种标准库模板类型。用于表示某种特定类型的值的数组。该值为常量值，无法修改。
表6.1 initializer_list 提供的操作。

# 6.3.3 返回值为数组指针
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
想要声明一个指向函数的指针变量，只需要用指针变量名替换函数名即可
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
# 7.0 类
通过定义新的类型来反映待解决问题中的各种概念，可以使我们更容易编写、调试、和修改程序。类的基本思想是数据抽象，封装，

# 7.1.5拷贝，赋值和析构，
对象在几种情况下会被拷贝：
1、变量初始化
2、以值的方式传递参数或返回对象，

使用赋值运算符

# 7.5.4 隐式的类类型转换 

# 8.1 IO类
使用IO操作处理string中的字符会很方便。（P278） 此话怎讲？

IO类型间的关系
# 8.1.1 IO对象无拷贝和赋值 
进行IO操作的函数通常以引用方式传递参数和返回流。读写一个IO对象会改变其状态，因此传递和返回的引用不能是const 修饰的。


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

# 9.1 顺序容器概述
 确定使用那种顺序容器。（P293）如何选择合适的顺序容器。

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
//特殊的forward_list单向链表 操作 P313
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
replace_copy(ilst.being(),ilst.end(),back_inserter(ivec),0,42);

```

# 10.2.3 重排容器元素的算法
消除重复单词：
首先sort 排序，
unique 重排，移动元素覆盖掉 重复的元素，
使用erase 删除 unique 返回的迭代器于原容器尾后迭代器之间的元素。 
```cpp
sort(words.bein(),words.end());
//
auto end_unique=unique(words.begin(),words.en());
//使用vector 操作erase 删除重复单词
words.erase(end_unique,words.end());//
```

 # 使用容器操作删除元素

# 10.3 定制操作

# 10.3.1 向算法传递函数

# 10.3.2 添加元素
检测insert 的返回值类型。添加一个元素的 insert和emplace 返回一个pair ,告诉插入是否成功，pair的first 成员是一个迭代器，指向具有给定关键字的元素，second成员是一个bool值。


# 10.3.2 lambda 表达式表示一个可调用的代码单元。可以理解为一个未命名的内联函数。（P346）
1、可以定义在函数内部。
2、必须使用尾后返回指定返回类型。（此处的必须强调的是返回类型的声明方式）
3、可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体。
4、lambda 不能有默认参数。
5、捕获列表只用于局部非static 变量，lambda可以直接使用局部static变量和定义在当前函数之外的名字
6、以传值参数类似，采用值捕获的前提是变量可以拷贝。捕获变量的值是在lambda创建时拷贝，不是调用时拷贝。
7、为了指示编译器推断捕获列表，应该在捕获列表中写一个&或=。&告诉编译器采用捕获引用方式，=则表示采用值捕获方式。
例如：
```cpp
auto f=[]{return 20;};
```
# 一个lambda 表达式具有如下形式
[capture list](parameter list)-> return type{ function body}
capture list 为捕获列表

lambda 以一对[]开始，我们在其中提供一个以逗号分隔的名字列表，这些名字都是它所在函数中定义的。

# lambda引用捕获

accumulate 算法 P338
equal 算法 P339
find 算法 P336
fill 算法 P340
fill_n 算法 P340
replace 算法 P342
replace_copy 算法 P342
partition 划分算法 P345 （练习 10.13）
copy 算法P341
erase 算法
unique 算法 P343
unique_copy
sort 算法
table_sort 排序算法 P347
find_if 算法 P346 P348
for_each 算法 P348
使用示例⬇⬇⬇⬇
##[Exercise 10.16](/CppPrimer-master/ch10/ex10_16.cpp)

# 10.3.4  参数绑定 标准库 bind函数  
 它定义在头文件functional中 ，可以将bind看作一个通用函数适配器，接受一个可调用对像（计做 对象1），生成一个新的可调用对象（记做对象2）来“适应” 或适配泛型算法函数的谓词参数 （P354）
 对象1 ：是一个有多个参数的自定义函数
 对象2:适配器bind 生成的一个符合谓词参数的函数
 函数对象1 定义如下：
 对象1（参数1，参数2，参数3，_2,参数4，_1,其它参数....）;

对象2= bind（对象1，参数1，参数2，参数3，_2,参数4，_1,其它参数....） ;

对象2（_1，_2）;此处的参_1 会传递给上述 站位符_1, 此处的参数_2会传给上述站位符_2;

bind 做了什么？ 
 1、绑定谓词不能接受的剩余参数；（函数重载）
 2、新的的调用对象的参数，绑定到占位符上。
 3、如果我们希望传递给bind的参数是一个引用，就必须使用标准库 ref 函数

 ```cpp
 //IO 类的对象是不支持拷贝赋值的。只能是引用或指针。
 for_each(words.begin(),words.end(),bind(print,ref(os),_1,' '));
//函数ref 返回一个对象，包含给定的引用。此对象可以拷贝。
 ```
# 10.4 在探迭代器


# 10.4.1 节练习
unique_copy 算法
## [Exercise 10.27](/CppPrimer-master/ch10/ex10_27.cpp)
 

 # 10.4.2 iostream 迭代器
 使用算法操作流迭代器（P360）
 ## ostream_iterator 操作 创建一个ostream_iterator 时必须将ostream_iterator 绑定到一个指定的流，不允许创建一个空的或表示尾后位置的ostream_iterator。 我们还可以提供一个可选的第二参数，它是一个字符串，在输出每个元素后都会打印此字符串，此字符串是一个C风格字符串。
 ## [Exercise 10.33](/CppPrimer-master/ch10/ex10_33.cpp)
# 10.4.3 反向迭代器（reverse_iterator） base 成员函数返回其对应的普通迭代器；
使用范例;
## [Exercise 10.34 ~ 10.37](/CppPrimer-master/ch10/ex10_34_35_36_37.cpp)
反向迭代器的目的是表示元素范围，而这些元素范围是不对称的，这导致一个重要的结果：当我们从一个谱通迭代器初始化一个反向迭代器，或是给一个反向迭代器赋值时，结果迭代器与原迭代器指向的不是相同的元素。需调用其成员函数base() .返回指向正确位置的迭代器。

#  11.0 关联容器 
当想知道一个值是否存在时，set是最有用的。


# 11.2.2 关键字类型的要求
有序容器的关键字类型 可以向一个算法提供给我们自己定义的比较操作。以之类似，也可以提供自己定义的操作来代替关键字上的 < 运算符

使用关键字类型的比较函数。————用来组织一个容器中元素操作的类型也时该容器类型的一部分，为了指定使用自定义的操作。必须在定义关联容器类型时提供此操作的类型。

```cpp
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

using compareType = bool (*)(const Sales_data &lhs, const Sales_data &rhs);
//typedef bool(*compareType)(const Sales_data &lhs, const Sales_data &rhs);
//为了使用自定义的操作，在定义multiset时我们必须提供两个类型。关键字类型，关键字比较操作类型
std::multiset<Sales_data, compareType> bookstore(compareIsbn);

//关键字类型为 Sales_data 
//关键字类型的比较函数 compareIsbn
//

```
# 11.3.3 删除元素

# 11.3.4 map的下标操作
使用下标操作的返回值类型为mapped_type对象，解引用一个map迭代器时会得到一个value_type对象，
与vector 与string 不同，map的下标运算符返回的类型与解引用map 迭代器得到的类型不同。

# 11.3.5 访问元素
如果我们所关心的只不过是一个特定元素是否已在容器中，find 是最佳选择。如果使用下标获取元素，当元素不存在时会插入一个新元素。
表11.7 在一个关联容器中查找元素操作（P388）
一种不同的，面向迭代器的解决方法。


# 11.4 无需容器
不是使用比较运算符来组织元素，而是使用一个hash function 和关键字类型== 运算符。在关键字没有明显的序关系的情况下。无序容器时非常有用的。
# 使用无序容器————无序容器在存储上组织为一组桶，每个桶保存零个或多个元素。（P395）
# 管理桶 表11.8 无序容器管理操作。
# 无序容器对关键字类型的要求
不能直接定义关键字类型为自定义类型的无序容器。与容器不同不能直接使用哈希模板，而必须提供自己的hash模板版本。

# 12 动态内存

# 12.1 动态内存与智能指针
表12.1 shared_ptr和unique_ptr   都支持的操作（P401）

需要注意的几个成员：
get函数 返回一个内置指针，指向只能指针管理的对象，该函数是为了这样一种情况而设计的：我们需要像不能使用智能指针的代码传递一个内置指针。使用get 返回的指针的代码不能delete 此指针。

reset 函数 将一个新的指针赋予一个shared_ptr （P414）
```cpp
p=new int(1024);//错误：不能将一个指针赋予shared_ptr;
p.reset(new int(1024));//正确 p指向一个新对象
```
reset 成员经常与unique 成员一起使用，可以控制多个shared_ptr共享的对象，
```cpp
if(!p.unique()){
    p.reset(new string(*p));//我们不是唯一的用户；分配新的拷贝
}
*p +=newVal;//现在我们知道自己已是唯一的用户，可以改变对象的值
```
# 使用我们自己的释放操作（P416）
使用shared_ptr来保证connection被正确关闭，已被证明是一种有效的方法。

```cpp
void f(destination &d)
{
    connection conn = connect(&d);
    std::shared_ptr<connection> p(&conn, end_connection);
    std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}
//单 函数退出时（异常退出） connection 会被正确关闭，当p被销毁时，调用的是 end_connection 
```
//使用的例子
## [Exercise 12.14](/CppPrimer-master/ch12/ex12_14.cpp)
 

make_shared 函数
最安全的分配和使用动态内存的方法是调用一个名为make_shared的标准库函数。

shared_ptr 的拷贝和赋值
shared_ptr自动销毁所管理的对象，还会自动释放相关联的内存。由于在最后一个shared_ptr 销毁前，内存都不会释放。保证shared_ptr在无用之后不再保留就非常重要了。

# 使用了动态生存期的资源的类

程序使用动态内存出于一下三种原因之一：（P403）
1、程序不知道自己需要使用多少对像。
2、程序不知道所需对象的准确类型。（15章）
3、程序需要在多个对象之间共享数据。
容器类出于第一种原因而使用动态内存的典型例子。

动态分配的const 对象（P408）
内存耗尽；

智能指针陷阱（P417）

std::shared_ptr 自身的有效期

其有效期（ 生命周期）受其引用计数控制，具体如下：
对象的有效期：
1、std::shared_ptr 所指向的对象的有效期由其引用计数决定。只要有一个 std::shared_ptr 指向该对象，引用计数就会大于零，表示对象仍然存活。当所有的 std::shared_ptr 都不再指向该对象时，引用计数降为零，随后对象将被销毁。

2、std::shared_ptr 本身的有效期由其指向的对象和其他 shared_ptr 引用的存在与否决定。当 shared_ptr 不再使用时，它自身会被销毁。

std::shared_ptr 本身并没有直接提供检测对象是否已经销毁的功能，不过可以通过 std::weak_ptr 来实现这一需求。std::weak_ptr 是一种不影响对象生命周期的弱引用，可以检测到对象是否已经销毁。

通过std::weak_ptr 可以阻止用户访问一个不再存在的 shared_ptr 

什么情况下 std::shared_ptr  的引用计数为0；

# 12.1.5 unique_ptr;
不支持 普通的拷贝或赋值操作。我们可以拷贝和赋值一个将要销毁的unique_ptr(编译器执行一种特殊的拷贝) （P418）
```cpp
unique_ptr<int> clone(int p) {
    // ok: explicitly create a unique_ptr<int> from int*
    return unique_ptr<int>(new int(p));
}
```

# 向unique_ptr 传递删除器
# 指向数组的unique_ptr，我们不能使用点和箭头成员运算符，我们可以使用下标运算符来访问数组中的元素
```cpp
unique_ptr<int[]> up new(int [10]);
for(size_t i=0;i!=10;i++){
    up[i]=i;
}
up.release();//自动用delete [] 销毁其指针
```
//不推荐使用shared_ptr管理动态数组
与unique_ptr不同 shared_ptr不能直接支持管理动态数组。如果希望使用 shared_ptr管理一个动态数组，必须提供自定义的删除器。
```cpp
shared_ptr<int> sp(new int[10],[](int*p){delete []p;});
sp.reset();

```
# 向unique_ptr   转递删除器 

12.2.2 allocator 类 声明在头文件 memory 中

与new的区别 new ---分配内存的同时初始化。

allocator 分配内存时：将内存分配和对象构造分开。 意味着我们可以分配大块内存，只在真正需要时才真正执行对象创建操作。
表12.7 标准库allocator类及其算法(P428)
allocator 分配未构造的内存

# 拷贝和填充未初始化内存算法

# 12.3使用标准库：文本查询程序
## Exercise 12.30 [Header](/CppPrimer-master/ch12/ex12_27_30.h)|[Implementation](/CppPrimer-master/ch12/ex12_27_30.cpp)|[Test](/CppPrimer-master/ch12/ex12_27_30_TEST.cpp)


# 14.9.1 类型转换运算符 ————类型转换运算符是类的一种特殊成员函数，
operator type()const;
因为类型转换运算符是隐式执行的，所以无法给这些函数转递实参，也就不能在类型转换运算符的定义中使用任何形参。


# 关键字 说明及使用示例列表
[explicit](/CppPrimer-master/keyword/explicit.md)
[friend](/CppPrimer-master/ch14/ex14_02.h)
[inline](/CppPrimer-master/ch14/ex14_02.h)
[operator>>](/CppPrimer-master/ch14/ex14_02.h)
[operator<<](/CppPrimer-master/ch14/ex14_02.h)
[operator+](/CppPrimer-master/ch14/ex14_02.h)
[operator+=](/CppPrimer-master/ch14/ex14_02.h)
[operator==](/CppPrimer-master/ch14/ex14_16_String.h)
[operator!=](/CppPrimer-master/ch14/ex14_16_String.h)
[operator=]()
类型转换运算符 
[operator type()]()

# 类型别名 typdef 、using


# 类
# 当我们设计类时：
类（动物、植物，人类，鱼类）相同的属性--->类的数据成员 相同的动作 函数成员
做法1: 在真正实现成员之前先编写程序使用这个类（需要提供哪些操作），通过这个方法可以看到类是否具有所需要的操作。确定类需要的操作之后，才能思考到底应该把每个类操作设成普通函数，还是重载运算符。
做法2：对于公共的代码使用私有功能函数 P248 建议


需要控制类型转换
需要控制如何初始化，
需要控制拷贝
需要控制赋值
需要控制销毁
------ 需要考虑使用场景
静态成员函数，静态成员变量---->单例时需要
# 构造函数
特点：
不能有返回值
explicit 构造函数只能用于直接初始化；（P265）只对一个实惨的构造函数有效。
加了关键字 explicit 修饰的构造函数 构造对象时只能显示的调用对应的版本构造对象。

在 C++ 中，explicit 关键字用于防止构造函数进行隐式转换。通过 explicit 关键字声明的构造函数，只能通过显式调用来创建对象。

constexpr 构造函数（P267）
# const 成员函数声明

int func(string s)const 

constexpr 函数的要求 唯一可执行语句就是返回语句。也可以是空语句，这里的const 作用的是this指向的对象。

虚表指针，虚函数，纯虚函数，虚函数指针。

# 类可以允许其他类或者函数（非成员函数）访问它的非公有成员，方法时令其他类或者函数成为它的友元（friend）
friend 关键字修饰的类，或者函数。（P241、P250）
每个类负责控制自己的友元类或友元函数

## Exercise 7.26 [Header](/CppPrimer-master/ch07/ex7_26.h)|[CPP](/CppPrimer-master/ch07/ex7_26.cpp)


# 在类之间共享数据方法归纳如下：
shared_ptr (P431)


# 模板 ————C++语言既有类模板也有函数模板 其中vector 是一个类模板，模板本身不是类也不是函数，相反可以看作为编译器生成类或函数编写的一份说明，
编译器根据模板来创建类或函数的过程称为实例化，当使用模板时需要指出编译器应把类模板或函数模板实例化成何种类型或函数。


关键字 [意味着]出现的地方 P424 
[值的注意] 出现的地方 P421
[值得注意]出现的地方 P477 最后一行

[遗留的问题]
智能指针 unique_ptr 使用场景？？ 表12.6指向数组的unique_ptr （P426）
可变参数模板（P618）?

 所有权概念？ std::move 函数 

 类的设计，是围绕着需要用到标准库容器和算法来设计的。令该类可以使用这些算法和容器以并满足使用迭代器的要求。

 C++ 左值应用与右值引用的使用场景？
Ai的回答
 返回引用：函数返回左值引用，可以用于链式调用或允许对返回值进行修改。

 移动语义：右值引用用于实现移动构造函数和移动赋值运算符，从而避免不必要的深拷贝，优化性能。

[遗留问题10]：tcp包如何区分同一个连接的不同api请求？
tcp 包是无法区分的，也不需要区分；
http属于应用层协议，有完整的协议格式

[遗留问题11]http 如何区分同一个API接口的并发请求对应的服务器响应？

[遗留问题12]socket 高并发编程，是如何实现的？
总结
- 左值引用（Lvalue Reference）
- 定义：用于引用左值（具有持久存储的对象）。
- 适用场景：
- 传递参数以避免拷贝。
- 函数返回引用以实现链式调用或修改返回值。
- 右值引用（Rvalue Reference）
- 定义：用于引用右值（临时对象或字面值）。
- 适用场景：
- 实现移动语义以避免不必要的深拷贝。
- 模板函数中用于完美转发以保持参数的左值或右值特性。
- 通过正确使用左值引用和右值引用，可以大幅优化程序性能，尤其是涉及到资源管理和大型对象时，它们都是强大的工具。

练手项目 
[多人聊天支持文件传输]


对[类]的一些思考
1、应该如何设计？
2、C++ 如何决定类与类之间的关系？
3、何时使用friend ？
4、C++ 类如何解决实际问题？

标准库的一下问题
1、新标准的最主要的特性是哪些？
2、C++ 标准库容器对异常发生时其自身的行为提供保障，是怎么做的？[具体做法](/CppPrimer-master/STL/noexcept.md)
3、C++ 开发准则 C++ Core Guidelines [开发指南](/CppPrimer-master/STL/C++%20Core%20Guidelines.md)
4、[C++ 三大标准 四大范式](/CppPrimer-master/STL/三大标准四大范式.md)
5、[C++ 函数调用匹配原则](/CppPrimer-master/STL/C++%20函数调用匹配原则.md)
6、[编译器会在一些特定情况下自动生成（或“合成”）某些成员函数](/CppPrimer-master/STL/C++编译器生成拷贝控制成员的原则.md)