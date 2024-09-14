#include <stdio.h>

void Delete(int a[], int *n, int start, int end) {
    for (int i = end + 1; i < *n; ++i) {
        a[i - (end - start + 1)] = a[i];
    }
    *n = *n - (end - start + 1);
}


int main() {
    int a[1000];
    int n;
    int start;
    int end;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }
    scanf("%i %i", &start, &end);


    Delete(a, &n, start, end - 1);


    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}