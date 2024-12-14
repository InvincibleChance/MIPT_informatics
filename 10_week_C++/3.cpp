#include <iostream>
#include <vector>
#include <string>
#include <utility> // Для std::pair
#include <algorithm> // Для std::min_element и std::max_element

// Шаблонная функция minmax
template<typename T>
std::pair<T, T> minmax(const std::vector<T>& v) {
    // Находим минимальный и максимальный элементы
    T min = *std::min_element(v.begin(), v.end());
    T max = *std::max_element(v.begin(), v.end());
    return {min, max};
}

int main() {
    // Тест с int
    std::vector<int> a {60, 10, 40, 80, 30};
    auto am = minmax(a);
    std::cout << am.first << " " << am.second << std::endl; // 10 80

    // Тест со std::string
    std::vector<std::string> b {"Cat", "Dog", "Mouse", "Camel", "Wolf"};
    auto bm = minmax(b);
    std::cout << bm.first << " " << bm.second << std::endl; // Camel Wolf

    // Тест с std::pair<int, int>
    std::vector<std::pair<int, int>> c {{10, 90}, {30, 10}, {20, 40}, {10, 50}};
    auto cm = minmax(c);
    std::cout << cm.first.first << " " << cm.first.second << std::endl; // 10 50
    std::cout << cm.second.first << " " << cm.second.second << std::endl; // 30 10
}
