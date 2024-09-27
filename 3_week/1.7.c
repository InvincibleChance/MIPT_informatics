#include <stdio.h>

int main() {
    printf("char: %zu байт\n", sizeof(char));
    printf("short: %zu байт\n", sizeof(short));
    printf("int: %zu байт\n", sizeof(int));
    printf("long long: %zu байт\n", sizeof(long long));
    printf("size_t: %zu байт\n", sizeof(size_t));
    printf("float: %zu байт\n", sizeof(float));
    printf("double: %zu байт\n", sizeof(double));
    printf("int[10]: %zu байт\n", sizeof(int[10]));
    printf("char[10]: %zu байт\n", sizeof(char[10]));

    return 0;
}