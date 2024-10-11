#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    char title[50];
    int pages;
    float price;
};

typedef struct book Book;

void print_book(Book *b) {
    printf("Title: %s\n", b->title);
    printf("Pages: %d\n", b->pages);
    printf("Price: %.2f\n", b->price);
}

int main() {
    Book *p = (Book *)malloc(sizeof(Book));

    if (p == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    strcpy(p->title, "Don Quixote");
    p->pages = 1000;
    p->price = 750.0;

    print_book(p);

    free(p);

    return 0;
}
