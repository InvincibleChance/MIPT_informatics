#include <stdio.h>


void Delete_negative(int a[], int *n) {
    int j = 0;
    for (int i = 0; i < *n; ++i) {
        if (a[i] >= 0) {
            a[j] = a[i];
            j += 1;
        }
    }
    *n = j;
}

int main() {
    int a[1000];
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }

    Delete_negative(a, &n);


    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}
