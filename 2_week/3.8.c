#include <stdio.h>

void reversee(int arr[], int size) {
    int new_arr[size];
    for (int i = 0; i <= size; ++i) {
        new_arr[i] = arr[size - i - 1];
    }
    for (int i = 0; i < size; ++i) {
        printf("%i ", new_arr[i]);
    }
}

int main() {
    int n;
    scanf("%i", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }
    reversee(arr, n);
}