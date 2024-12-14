#include <iostream>
#include <type_traits>
#include <cstdint>


template<typename T>
void swapEndianness(T &value) {
    uint8_t *bytes = reinterpret_cast<uint8_t *>(&value);
    size_t size = sizeof(T);

    for (size_t i = 0; i < size / 2; ++i) {
        std::swap(bytes[i], bytes[size - i - 1]);
    }
}


int main() {
    std::cout << std::hex;
    int a = 0x1a2b3c4d;
    std::cout << a << std::endl; // Должен напечатать 1a2b3c4d
    swapEndianness(a);
    std::cout << a << std::endl; // Должен напечатать 4d3c2b1a
    swapEndianness(a);
    std::cout << a << std::endl; // Должен напечатать 1a2b3c4d
    short b = 0x1a2b;
    std::cout << b << std::endl; // Должен напечатать 1a2b
    swapEndianness(b);
    std::cout << b << std::endl; // Должен напечатать 2b1a
}