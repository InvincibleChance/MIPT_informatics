#include <stdio.h>
#include <stddef.h>
#include <stddef.h>

struct cat {
    char x;
    size_t y;
};

struct dog {
    size_t y;
    char x;
};

struct mouse {
    char x;
    char y;
    size_t z;
};

struct rat {
    char x;
    size_t z;
    char y;
};

struct fox {
    char x;
    struct mouse y;
};

int main() {
    printf("Размер и выравнивание char:\n");
    printf("Size: %zu\n", sizeof(char));
    printf("Alignment: %zu\n\n", alignof(char));

    printf("Размер и выравнивание int:\n");
    printf("Size: %zu\n", sizeof(int));
    printf("Alignment: %zu\n\n", alignof(int));

    printf("Размер и выравнивание size_t:\n");
    printf("Size: %zu\n", sizeof(size_t));
    printf("Alignment: %zu\n\n", alignof(size_t));

    printf("Размер и выравнивание int[10]:\n");
    printf("Size: %zu\n", sizeof(int[10]));
    printf("Alignment: %zu\n\n", alignof(int[10]));

    printf("Размер и выравнивание int*:\n");
    printf("Size: %zu\n", sizeof(int *));
    printf("Alignment: %zu\n\n", alignof(int *));

    printf("Размер и выравнивание struct cat:\n");
    printf("Size: %zu\n", sizeof(struct cat));
    printf("Alignment: %zu\n\n", alignof(struct cat));

    printf("Размер и выравнивание struct dog:\n");
    printf("Size: %zu\n", sizeof(struct dog));
    printf("Alignment: %zu\n\n", alignof(struct dog));

    printf("Размер и выравнивание struct mouse:\n");
    printf("Size: %zu\n", sizeof(struct mouse));
    printf("Alignment: %zu\n\n", alignof(struct mouse));

    printf("Размер и выравнивание struct rat:\n");
    printf("Size: %zu\n", sizeof(struct rat));
    printf("Alignment: %zu\n\n", alignof(struct rat));

    printf("Размер и выравнивание struct fox:\n");
    printf("Size: %zu\n", sizeof(struct fox));
    printf("Alignment: %zu\n\n", alignof(struct fox));
}