#include <iostream>


std::string repeat(int n) {
    std::string result;
    std::string num = std::to_string(n);
    for (int i = 0; i < n; ++i) {
        result += num;
    }
    return result;
}


int main() {
    std::cout << repeat(5) << std::endl; // Должно напечатать 55555
    std::cout << repeat(10) << std::endl; // Должно напечатать 10101010101010101010
    std::cout << repeat(-1) << std::endl; // Не должно ничего печатать
}