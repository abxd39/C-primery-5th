/*
C++ 流迭代器是标准库中非常有用的工具，
它们允许我们以统一的方式处理不同类型的流
（如文件、字符串流、标准输入输出等）。
让我为您详细介绍一些流迭代器的经典用法。
流迭代器 实现惰性取值 惰性取值是一种编程策略 C++的标准库中并没有直接支持惰性求值的流（stream）概念 可以通过设计模式来实现类似功能(line:72)
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
    //使用 `std::istream_iterator<std::string>` 从文件中读取单词（以空白字符分隔）到一个 vector 中。
    std::vector<std::string> words(std::istream_iterator<std::string>(inputFile),
                                   std::istream_iterator<std::string>());

    // 4. 将数据写入文件
    std::ofstream outputFile("output.txt");
    //下面代码提示错误，如何修改？ 编辑器问题。无须在意
    //使用 `std::ostream_iterator<std::string>` 将 vector 中的单词写入文件，每个单词占一行。
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
    //使用 `std::copy_if` 和一个 lambda 函数，将只有偶数输出到标准输出。
    std::copy_if(integers.begin(), integers.end(),
                 std::ostream_iterator<int>(std::cout, " "),
                 [](int n) { return n % 2 == 0; });
    std::cout << std::endl;

    return 0;
}

/*

这些用法展示了流迭代器的灵活性和强大功能：

- 它们可以与各种流（cin, cout, fstream, stringstream 等）无缝配合。
- 可以轻松地与 STL 算法（如 copy, transform, copy_if 等）结合使用。
- 允许进行惰性求值，这在处理大型数据集时特别有用。
- 提供了一种统一的方式来处理不同类型的输入和输出。

在实际应用中，流迭代器特别适用于需要从各种源读取数据或将数据写入各种目的地的场景，
如文件处理、数据转换、日志分析等。它们也非常适合于构建数据处理管道，
其中数据可以被逐步读取、转换和写入。

*/

/*当然，我很乐意解释 istream_iterator 如何支持懒惰求值（lazy evaluation）。
这是 C++ 流迭代器的一个重要特性，特别是在处理大量数据或无限数据流时非常有用。

懒惰求值意味着数据只有在被实际需要时才会被读取和处理，而不是预先读取所有数据。
对于 istream_iterator 来说，这意味着它只有在你尝试访问它所指向的值时才会从流中读取数据。
*/
//让我们通过一个例子来详细说明这一点：


#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

class NumberGenerator {
private:
    int current;
public:
    NumberGenerator() : current(0) {}
    
    friend std::istream& operator >>(std::istream& is, NumberGenerator& ng) {
        std::cout << "Generating number: " << ng.current << std::endl;
        is.setstate(std::ios::failbit);
         is >> ng.current++;
         return is;
    }
};

int main() {
    NumberGenerator ng;
    std::istream_iterator<int> it(std::cin >> ng);
    std::istream_iterator<int> end;

    std::cout << "Iterator created, but no numbers generated yet.\n";

    std::vector<int> numbers;
    std::cout << "Copying first 5 numbers:\n";
    std::copy_n(it, 5, std::back_inserter(numbers));

    std::cout << "First 5 numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    std::cout << "Copying next 3 numbers:\n";
    std::copy_n(it, 3, std::back_inserter(numbers));

    std::cout << "All 8 numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}

/*

这个例子展示了 istream_iterator 的懒惰求值特性。让我解释一下代码的关键部分：

1. 我们定义了一个 `NumberGenerator` 类，它模拟了一个无限的数字流。每次从这个"流"中读取时，它会生成下一个数字并打印一条消息。

2. 在 `main()` 函数中，我们创建了一个 `istream_iterator<int>`，将其与我们的 `NumberGenerator` 关联。

3. 重要的是，在创建迭代器后，没有立即生成任何数字。这就是懒惰求值的体现。

4. 只有当我们使用 `std::copy_n` 来复制数字时，才会实际生成数字。每次 `copy_n` 需要下一个值时，它才会从迭代器中读取，进而触发 `NumberGenerator` 生成下一个数字。

5. 我们首先复制 5 个数字，然后再复制 3 个数字。你会看到，数字是在需要时才被生成的，而不是一次性全部生成。

这种懒惰求值的方式有几个重要的优点：

1. 内存效率：不需要一次性将所有数据加载到内存中。对于处理大文件或流时，这一点尤其重要。

2. 处理无限流：可以处理理论上无限的数据流，因为数据是按需生成的。

3. 性能优化：如果我们只需要处理部分数据，那么我们就不必读取或生成所有数据。

4. 灵活性：可以很容易地将这种方式与其他 STL 算法结合使用，如 `std::find_if`、`std::accumulate` 等。

在实际应用中，这种特性在处理大型文件、网络流或其他可能很大或理论上无限的数据源时特别有用。
例如，你可以使用这种方式来处理日志文件，或者实时处理传感器数据流，而不必担心内存溢出或长时间的初始化延迟。

这就是 istream_iterator 支持懒惰求值的方式。它提供了一种强大而灵活的方法来处理输入流，使得我们可以高效地处理各种规模的数据。

*/

/*
`istreambuf_iterator` 是 C++ 标准库中的另一种输入迭代器，它与 `istream_iterator` 类似，
但有一些重要的区别和特定用途。
让我们深入探讨 `istreambuf_iterator` 的用法和特点。
[mdn iostreambuf_iterator](https://learn.microsoft.com/zh-cn/cpp/standard-library/istreambuf-iterator-class?view=msvc-170)
*/



#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

int main() {
    // 1. 基本用法：从文件读取所有字符
    std::ifstream file("example.txt");
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    std::cout << "File content:\n" << content << std::endl;

    // 2. 计算文件大小
    file.seekg(0, std::ios::beg);  // 重置文件指针到开始
    size_t file_size = std::distance(std::istreambuf_iterator<char>(file),
                                     std::istreambuf_iterator<char>());
    std::cout << "File size: " << file_size << " bytes\n";

    // 3. 复制文件内容（高效）
    file.seekg(0, std::ios::beg);  // 再次重置文件指针
    std::ofstream output_file("copy.txt");
    std::copy(std::istreambuf_iterator<char>(file),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(output_file));

    // 4. 将文件内容转换为大写
    file.seekg(0, std::ios::beg);
    std::string upper_content;
    std::transform(std::istreambuf_iterator<char>(file),
                   std::istreambuf_iterator<char>(),
                   std::back_inserter(upper_content),
                   ::toupper);
    std::cout << "Uppercase content:\n" << upper_content << std::endl;

    // 5. 按行读取文件（对比 istream_iterator）
    file.seekg(0, std::ios::beg);
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<std::string>(file),
              std::istream_iterator<std::string>(),
              std::back_inserter(lines));
    std::cout << "Number of words: " << lines.size() << std::endl;

    // 6. 处理二进制数据
    std::ifstream binary_file("data.bin", std::ios::binary);
    std::vector<char> binary_data(std::istreambuf_iterator<char>(binary_file),
                                  std::istreambuf_iterator<char>());
    std::cout << "Binary data size: " << binary_data.size() << " bytes\n";

    return 0;
}

/*

这个示例展示了 `istreambuf_iterator` 的几个重要用法。让我们逐一解析：

1. 基本用法：
   使用 `istreambuf_iterator` 可以轻松地将整个文件内容读入一个字符串。这种方法非常高效，因为它直接操作底层的流缓冲区。

2. 计算文件大小：
   利用 `std::distance` 和 `istreambuf_iterator`，我们可以快速计算文件的大小，而不需要预先分配内存。

3. 复制文件内容：
   使用 `std::copy` 和 `istreambuf_iterator` 可以高效地复制文件内容。这种方法比逐字节读写更快，因为它直接操作缓冲区。

4. 文本转换：
   结合 `std::transform`，我们可以在读取文件内容的同时进行转换操作，如将文本转换为大写。

5. 按行读取文件：
   这个例子展示了 `istream_iterator` 的用法，对比 `istreambuf_iterator`。
   `istream_iterator` 会跳过空白字符，而 `istreambuf_iterator` 不会。

6. 处理二进制数据：
   `istreambuf_iterator` 特别适合处理二进制文件，因为它可以逐字节读取，不会对数据进行任何解释或转换。

`istreambuf_iterator` 的主要特点和优势：

1. 效率高：直接操作流的缓冲区，比 `istream_iterator` 更高效。

2. 保留所有字符：不会跳过空白字符，适合处理需要保留所有字符的情况。

3. 适合大文件：可以高效处理大文件，不需要一次性将整个文件加载到内存。

4. 二进制数据处理：非常适合处理二进制文件。

5. 与算法兼容：可以与 STL 算法无缝配合。

6. 灵活性：可以用于任何类型的输入流（文件、字符串流、标准输入等）。

使用注意事项：

1. 不进行格式化：不会执行任何格式化操作，如跳过空白或类型转换。

2. 性能考虑：虽然通常比 `istream_iterator` 快，但在某些情况下（如需要进行类型转换时）可能不是最佳选择。

3. 错误处理：需要注意处理流的错误状态，特别是在处理大文件或网络流时。

在实际应用中，`istreambuf_iterator` 特别适用于：

- 高效的文件复制和内容读取
- 二进制文件处理
- 需要保留所有字符（包括空白）的文本处理
- 大文件的流式处理

总的来说，`istreambuf_iterator` 是一个强大的工具，特别是在需要高效处理大量数据或二进制数据时。
它提供了一种简洁而高效的方式来处理各种输入流，使得文件和流处理变得更加简单和高效。

如果您对 `istreambuf_iterator` 的特定用法或在实际项目中的应用有任何疑问，请随时问我。
    
    */