#include <iostream>
#include <string>


template<typename T>
T triple(const T &x) {
    return 3 * x;
}

std::string triple(const std::string &s) {
    return s + s + s;
}

int main() {
    int a = 10;
    std::cout << triple(a) << std::endl; // Напечатает 30

    std::string b = "Cat";
    std::cout << triple(b) << std::endl; // Напечатает CatCatCat
}