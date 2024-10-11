#include <stdio.h>
#include <stdlib.h>


void print(int *a, size_t n) {
    for (size_t i = 0; i < n; ++i)
        printf("%i ", a[i]);
    printf("\n");
}


void sort(int *arr, size_t n, int (*comparator)(int a, int b)) {
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (comparator(arr[j], arr[j + 1]) > 0) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int less(int a, int b) {
    return a - b;
}

int greater(int a, int b) {
    return b - a;
}

int last_digit_less(int a, int b) {
    return (a % 10) - (b % 10);
}

int main() {
    int a[] = {32, 63, 29, 54, 81};

    sort(a, 5, less);
    print(a, 5);

    sort(a, 5, greater);
    print(a, 5);

    sort(a, 5, last_digit_less);
    print(a, 5);
}