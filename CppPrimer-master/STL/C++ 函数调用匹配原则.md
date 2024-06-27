在 C++ 中，函数调用的一般匹配和选择原则是通过函数重载解析过程（Overload Resolution）实现的。具体来说，当调用一个函数时，编译器依次根据以下几种情况来匹配最合适的函数签名：

### 函数匹配的基本过程

1. **搜集候选函数（Candidate Functions）**：
   * 编译器在当前作用域内找到所有与函数名匹配的重载函数。

2. **筛选可行函数（Viable Functions）**：
   * 只有那些参数数量符合调用要求并且参数类型可以通过类型转换匹配的函数才会被视为可行函数。

3. **计算转换等级（Conversion Ranks）**：
   * 对于每个参数，计算从实参类型到形参类型所需类型转换的等级。

4. **选择最优匹配（Best Match）**：
   * 根据转换等级，选择一个最优的可行函数。如果存在多于一个同样最优的可行函数，调用将是二义的（ambiguous），导致编译错误。

### 转换等级

从实参到形参的转换等级可以从好到差分为以下几类：

1. **精确匹配（Exact Match）**：
   * 实参与形参类型完全一致，或者是引用类型的替换（包括const和volatitle附加）。
   * 例如，同样类型的值传递、引用传递、const增加等。

2. **提升转换（Promotion）**：
   * 比如整型到更大整型（char -> int）、浮点数提升（float -> double）。

3. **标准转换（Standard Conversion）**：
   * 包括内建类型之间的转换（bool, int, float, etc.），继承中的基类指针/引用转换和void*转换。

4. **用户定义转换（User-defined Conversion）**：
   * 通过类的构造函数或者类型转换操作符进行转换。

5. **省略参数（Ellipsis）**：
   * 使用省略号`...`处理的参数。这种转换最弱，一般被认为是最后一选。

### 示例

以下是一个简单示例来说明函数调用匹配原则：

```cpp
#include <iostream>

void func(int x) {
    std::cout << "Function with int" << std::endl;
}

void func(double x) {
    std::cout << "Function with double" << std::endl;
}

void func(float x) {
    std::cout << "Function with float" << std::endl;
}

int main() {
    func(10);      // 调用 func(int)
    func(10.5);    // 调用 func(double)
    func(10.5f);   // 调用 func(float)

    return 0;
}
```

### 二义性和匹配失败

如果存在二义性，编译器将无法确定应该调用哪个函数：

```cpp
#include <iostream>

void func(int x) {
    std::cout << "Function with int" << std::endl;
}

void func(double x) {
    std::cout << "Function with double" << std::endl;
}

int main() {
    func(10L);  // 会报错：无法确定调用 func(int) 还是 func(double)
    return 0;
}
```

在这种情况下，调用 `func(10L)` 会引起编译错误，因为 `10L` 是 `long` 类型，既可以提升为 `int` 也可以转换为 `double`，导致二义性。

### 总结

- **函数名匹配**: 编译器会首先寻找所有与函数名匹配的候选函数。
- **可行函数**: 只有参数数量和参数类型通过类型转换可以匹配的才会被认为是可行函数。
- **转换等级**: 从最佳到最差的转换级别来确定最优匹配的函数。
- **二义性检查**: 如果两个或更多可行函数具有相同的最优转换级别，编译器将报告二义性错误。

理解这些规则可以帮助你编写更清晰和健壮的函数重载代码，同时避免一些不必要的编译错误。