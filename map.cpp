#include <iostream>
#include <map>
#include <string>

void demonstrateMapOperations() {
    // 创建一个 string 到 int 的 map
    std::map<std::string, int> fruitCounts;

    // 插入元素
    fruitCounts["apple"] = 5;  // 使用 [] 运算符插入
    fruitCounts.insert(std::make_pair("banana", 3));  // 使用 insert 方法插入

    // 访问元素
    std::cout << "Apple count: " << fruitCounts["apple"] << std::endl;  // 使用 [] 访问
    std::cout << "Banana count: " << fruitCounts.at("banana") << std::endl;  // 使用 at() 方法访问

    // 检查元素是否存在
    if (fruitCounts.count("cherry") > 0) {
        std::cout << "Cherry exists in the map" << std::endl;
    } else {
        std::cout << "Cherry does not exist in the map" << std::endl;
    }

    // 使用迭代器遍历 map
    for (auto it = fruitCounts.begin(); it != fruitCounts.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    // 使用 range-based for 循环遍历 (C++11 及以上)
    for (const auto& pair : fruitCounts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 查找元素
    auto it = fruitCounts.find("banana");
    if (it != fruitCounts.end()) {
        std::cout << "Found banana: " << it->second << std::endl;
    }

    // 删除元素
    fruitCounts.erase("apple");  // 通过键删除

    // 获取 map 大小
    std::cout << "Map size: " << fruitCounts.size() << std::endl;

    // 检查 map 是否为空
    if (fruitCounts.empty()) {
        std::cout << "Map is empty" << std::endl;
    } else {
        std::cout << "Map is not empty" << std::endl;
    }

    // 清空 map
    fruitCounts.clear();

    // 使用 emplace 插入元素 (C++11 及以上)
    fruitCounts.emplace("orange", 7);

    // 获取第一个和最后一个元素
    if (!fruitCounts.empty()) {
        std::cout << "First element: " << fruitCounts.begin()->first << std::endl;
        std::cout << "Last element: " << (--fruitCounts.end())->first << std::endl;
    }

    // 使用 lower_bound 和 upper_bound
    auto lower = fruitCounts.lower_bound("orange");
    auto upper = fruitCounts.upper_bound("orange");

    // 交换两个 map
    std::map<std::string, int> otherMap{{"grape", 4}};
    fruitCounts.swap(otherMap);
}

//入口函数
int main() {
   demonstrateMapOperations();
    return 0;
}


