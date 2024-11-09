#include <iostream>

struct Book {
    std::string title;
    int pages;
    float price;
};


bool isExpensive(const Book &book) {
    return book.price > 1000;
}

int main() {
    Book my_book = {"Python", 1001, 5000.5};
    if (isExpensive(my_book)) {
        std::cout << "more then 1000" << std::endl;
    } else {
        std::cout << "less then 1000" << std::endl;
    }
    isExpensive(my_book);
}
