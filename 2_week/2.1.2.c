#include <stdio.h>

void Insert(int a[], int *n, int new_element, int index) {
    scanf("%i %i", &new_element, &index);
    for (int i = *n - 1; i > index; --i) {
        a[i + 1] = a[i];
    }
    a[index + 1] = new_element;
    (*n)++;
}

int main() {
    int a[1000];
    int n;
    int new_element;
    int index;

    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }

    Insert(a, &n, new_element, index);

    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}