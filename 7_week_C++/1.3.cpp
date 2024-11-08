#include <iostream>

namespace mipt {
    namespace fefm {
        struct Point {
            int x, y;
        };
    }

    namespace frtk {
        void print(fefm::Point p) {
            std::cout << p.x << " " << p.y << std::endl;
        }
    }
}

using mipt::fefm::Point;
using mipt::frtk::print;


int main() {
    Point p = {10, 20}; // Создание переменной типа Point
    print(p); // Вызов функции print
    return 0;
}
