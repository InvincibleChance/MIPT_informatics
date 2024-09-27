#include <stdio.h>
#include <limits.h>


unsigned long long arr(int n, int k) {
    unsigned long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= n - i;
        if (result > ULLONG_MAX) {
            printf("Результат превышает 2^64\n");
        }
    }
    return result;
}

int main() {
    int n, k;
    scanf("%i %i", &n, &k);
    unsigned long long result = arr(n, k);
    printf("%llu\n", result);
}