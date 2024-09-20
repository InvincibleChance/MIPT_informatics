#include <stdio.h>


int cube(int n) {
    n = n * n * n;
    return n;
}

int main() {
    int n;
    scanf("%i", &n);
    printf("%i\n", cube(n));
}