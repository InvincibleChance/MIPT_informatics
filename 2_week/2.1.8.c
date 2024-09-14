#include <stdio.h>

void printArray(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}

void Reverse(int a[], int k, int n) {
    int neww[1000];
    for (int i = 0; i < n; ++i) {
        neww[i] = a[i];
    }
    for (int i = 0; i < n; ++i) {
        a[(i + k) % n] = neww[i];
    }
}

int main() {
    int a[1000];
    int n;
    int k;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }


    scanf("%i", &k);
    Reverse(a, k, n);


    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}