/*
C++ 流迭代器是标准库中非常有用的工具，
它们允许我们以统一的方式处理不同类型的流
（如文件、字符串流、标准输入输出等）。
让我为您详细介绍一些流迭代器的经典用法。

*/
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

int main() {
    // 1. 从标准输入读取数据到容器
    std::cout << "Enter some numbers (Ctrl+D to end):\n";
    std::vector<int> numbers(std::istream_iterator<int>(std::cin),
                             std::istream_iterator<int>());

    // 2. 将容器内容输出到标准输出
    std::cout << "Numbers you entered:\n";
    std::copy(numbers.begin(), numbers.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // 3. 从文件读取数据
    std::ifstream inputFile("input.txt");
    std::vector<std::string> words(std::istream_iterator<std::string>(inputFile),
                                   std::istream_iterator<std::string>());

    // 4. 将数据写入文件
    std::ofstream outputFile("output.txt");
    //下面代码提示错误，如何修改？
    std::copy(words.cbegin(), words.cend(),
              std::ostream_iterator<std::string>(outputFile, "\n"));
    // 5. 使用流迭代器进行数据转换
    std::istringstream iss("1 2 3 4 5");
    std::vector<int> integers;
    std::transform(std::istream_iterator<std::string>(iss),
                   std::istream_iterator<std::string>(),
                   std::back_inserter(integers),
                   [](const std::string& str) { return std::stoi(str); });

    // 6. 使用流迭代器进行过滤
    std::copy_if(integers.begin(), integers.end(),
                 std::ostream_iterator<int>(std::cout, " "),
                 [](int n) { return n % 2 == 0; });
    std::cout << std::endl;

    return 0;
}

/*

这个代码示例展示了 C++ 流迭代器的几种经典用法。让我们逐一解析：

1. 从标准输入读取数据到容器：
   使用 `std::istream_iterator<int>` 从标准输入读取整数，直到遇到文件结束符（在 Unix 系统中是 Ctrl+D）。这些整数被直接存储到一个 vector 中。

2. 将容器内容输出到标准输出：
   使用 `std::ostream_iterator<int>` 将 vector 中的整数输出到标准输出。第二个参数 " " 指定了每个输出元素之间的分隔符。

3. 从文件读取数据：
   使用 `std::istream_iterator<std::string>` 从文件中读取单词（以空白字符分隔）到一个 vector 中。

4. 将数据写入文件：
   使用 `std::ostream_iterator<std::string>` 将 vector 中的单词写入文件，每个单词占一行。

5. 使用流迭代器进行数据转换：
   从字符串流中读取字符串，然后使用 `std::transform` 和一个 lambda 函数将这些字符串转换为整数。

6. 使用流迭代器进行过滤：
   使用 `std::copy_if` 和一个 lambda 函数，将只有偶数输出到标准输出。

这些用法展示了流迭代器的灵活性和强大功能：

- 它们可以与各种流（cin, cout, fstream, stringstream 等）无缝配合。
- 可以轻松地与 STL 算法（如 copy, transform, copy_if 等）结合使用。
- 允许进行惰性求值，这在处理大型数据集时特别有用。
- 提供了一种统一的方式来处理不同类型的输入和输出。

在实际应用中，流迭代器特别适用于需要从各种源读取数据或将数据写入各种目的地的场景，
如文件处理、数据转换、日志分析等。它们也非常适合于构建数据处理管道，
其中数据可以被逐步读取、转换和写入。

如果您对这些用法有任何疑问，或者想了解更多关于流迭代器的信息，请随时告诉我。
*/