#include <stdio.h>

void Delete(int a[], int *n, int index_delete) {
    scanf("%i", &index_delete);
    for (int i = index_delete; i < *n - 1; ++i) {
        a[i] = a[i + 1];
    }
    *n = *n - 1;
}


int main() {
    int a[1000];
    int n;
    int index_delete;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }


    Delete(a, &n, index_delete);


    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}
