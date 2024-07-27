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