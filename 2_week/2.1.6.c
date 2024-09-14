#include <stdio.h>


void Remake_array(int a[], int n) {
    int left = 0, right = n - 1;

    while (left < right) {
        while (left < right && a[left] % 2 != 0) {
            left++;
        }

        while (left < right && a[right] % 2 == 0) {
            right--;
        }

        if (left < right) {
            int temporary = a[left];
            a[left] = a[right];
            a[right] = temporary;
        }
    }
}


int main() {
    int a[1000];
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%i", &a[i]);
    }

    Remake_array(a, n);

    for (int i = 0; i < n; ++i) {
        printf("%i ", a[i]);
    }
    printf("\n");
}
