#include <stdio.h>


void DoubleArray(int a[], int *n) {
    int original_size = *n;
    *n = original_size * 2;
    for (int i = original_size - 1; i >= 0; --i) {
        a[2 * i + 1] = a[i];
        a[2 * i] = a[i];
    }
}

int main() {
    int a[1000];
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }

    DoubleArray(a, &n);

    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}