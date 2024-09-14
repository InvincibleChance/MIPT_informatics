#include <stdio.h>

void Doublee(int a[], int *n) {
    for (int i = *n; i < (*n) * 2; ++i) {
        a[i] = a[i - *n];
    }
    *n = *n * 2;
}


int main() {
    int a[1000];
    int n;

    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }

    Doublee(a, &n);

    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}