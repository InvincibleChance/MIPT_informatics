#include <stdio.h>

int count_even(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%i", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }

    int even_count = count_even(arr, n);
    printf("%i\n", even_count);
}