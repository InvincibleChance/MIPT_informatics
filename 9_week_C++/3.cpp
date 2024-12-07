#include <iostream>
#include <string>
#include <vector>

int main() {
    int *int_ptr = new int(123);
    std::cout << "int: " << *int_ptr << std::endl;

    std::string *str_ptr = new std::string("Cats and Dogs");
    std::cout << "string: " << *str_ptr << std::endl;

    int *int_array = new int[5]{10, 20, 30, 40, 50};
    std::cout << "int array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << int_array[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> *vec_ptr = new std::vector<int>{10, 20, 30, 40, 50};
    std::cout << "vector: ";
    for (int val: *vec_ptr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;


    std::string *str_array = new std::string[3]{"Cat", "Dog", "Mouse"};
    std::cout << "string array: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << str_array[i] << " ";
    }
    std::cout << std::endl;

    delete int_ptr;
    delete str_ptr;
    delete[] int_array;
    delete vec_ptr;
    delete[] str_array;
}
