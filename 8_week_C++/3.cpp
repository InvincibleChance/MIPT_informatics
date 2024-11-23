#include "number.hpp"
#include <iostream>

Number::Number() : data(new char[1]{0}), size(1), capacity(1) {
}

Number::Number(const Number &n) : size(n.size), capacity(n.capacity) {
    data = new char[capacity];
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = n.data[i];
    }
}


Number::Number(const std::string &str) {
    size = (str.length() + 1) / 2;
    capacity = size;
    data = new char[capacity];
    std::size_t str_index = str.length();
    for (std::size_t i = 0; i < size; ++i) {
        char digit1 = (str_index > 1) ? str[str_index - 2] - '0' : 0;
        char digit2 = str[str_index - 1] - '0';
        data[i] = digit1 * 10 + digit2;
        str_index = (str_index > 2) ? str_index - 2 : 0;
    }
}


int main() {
    Number num1;
    std::cout << "Default constructor: " << num1 << std::endl;

    Number num2(12345678);
    std::cout << "Original number: " << num2 << std::endl;

    Number num3 = num2;
    std::cout << "Copied number: " << num3 << std::endl;

    Number num4("987654321");
    std::cout << "Number from odd-length string: " << num4 << std::endl;
}