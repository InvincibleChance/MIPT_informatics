#include <stdio.h>

int main() {
    int number;
    scanf("%i", &number);
    for (int k=1;k<=number; k++){
        printf("%3i -> %3i ->%3i\n", k, k*k, k*k*k);
    };
}
