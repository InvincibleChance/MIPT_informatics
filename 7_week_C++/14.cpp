#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::size_t> &v) {
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

std::vector<std::size_t> substringIndexes(const std::string first, const std::string second) {
    std::vector<std::size_t> index;
    std::size_t position = first.find(second);
    while (position != std::string::npos) {
        index.push_back(position);
        position = first.find(second, position + 1);
    }
    return index;
}


int main() {
    std::vector<std::size_t> v1 = substringIndexes("cat and dog and cat", "cat");
    print(v1); // Должно напечатать 0 16
    std::vector<std::size_t> v2 = substringIndexes("look, cats were here", "cat");
    print(v2); // Должно напечатать 6
    std::vector<std::size_t> v3 = substringIndexes("catcatcatcatcatcat", "cat");
    print(v3); // Должно напечатать 0 3 6 9 12 15
    std::vector<std::size_t> v4 = substringIndexes("dog mouse elephant", "cat");
    print(v4); // Не должно ничего печатать
}
