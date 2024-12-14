#include <iostream>
#include <string>


std::string operator*(int n, std::string s) {
    std::string result;
    for (int i = 0; i < n; ++i) {
        result += s;
    }
    return result;
}


template<typename T>
T triple(const T &x) {
    return 3 * x;
}

int main() {
    int a = 10;
    std::cout << triple(a) << std::endl; // Напечатает 30

    std::string b = "Cat";
    std::cout << triple(b) << std::endl; // Напечатает CatCatCat
}
