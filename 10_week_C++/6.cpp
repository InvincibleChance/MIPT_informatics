#include <iostream>
#include <type_traits>

template<typename T, T Mod>
class Modular {
private:
    T value;

    T normalize(T v) const {
        T result = v % Mod;
        if (result < 0) result += Mod;
        return result;
    }

public:
    explicit Modular(T v) : value(normalize(v)) {
    }

    Modular(const Modular &other) : value(other.value) {
    }

    template<typename U, U OtherMod>
    explicit Modular(const Modular<U, OtherMod> &other) : value(normalize(other.getValue())) {
    }

    Modular &operator=(const Modular &other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }

    Modular operator+(const Modular &other) const {
        return Modular(value + other.value);
    }

    Modular operator-(const Modular &other) const {
        return Modular(value - other.value);
    }

    Modular operator*(const Modular &other) const {
        return Modular(value * other.value);
    }

    Modular operator+(T num) const {
        return Modular(value + num);
    }

    Modular operator-(T num) const {
        return Modular(value - num);
    }

    Modular operator*(T num) const {
        return Modular(value * num);
    }

    Modular operator-() const {
        return Modular(-value);
    }

    friend std::ostream &operator<<(std::ostream &os, const Modular &mod) {
        os << mod.value;
        return os;
    }

    T getValue() const {
        return value;
    }
};

int main() {
    Modular<int, 7> a(10);
    std::cout << a << std::endl; // Напечатает 3

    a = (a + 8) * 4;
    std::cout << a << std::endl; // Напечатает 2

    Modular<int, 7> b(a);
    b = b + 2;
    a = a - b;
    std::cout << a << std::endl; // Напечатает 5

    Modular<short, 3> c(a);
    std::cout << c << std::endl; // Напечатает 2

    return 0;
}