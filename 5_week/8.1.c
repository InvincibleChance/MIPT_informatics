#include <stdio.h>


int adder(int num) {
    static int sum = 0;
    sum += num;
    return sum;
}

int main() {
    printf("%i\n", adder(10)); // Должен напечатать 10
    printf("%i\n", adder(15)); // Должен напечатать 25
    printf("%i\n", adder(70)); // Должен напечатать 95
    return 0;
}