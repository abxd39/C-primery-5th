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