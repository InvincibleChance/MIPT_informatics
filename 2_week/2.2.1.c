#include <stdio.h>

int main() {
    int n;
    int m;
    scanf("%i %i", &n, &m);

    int columnSums[m];

    for (int i = 0; i < m; ++i) {
        columnSums[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int element;
            scanf("%i", &element);
            columnSums[j] += element;
        }
    }

    for (int i = 0; i < m; ++i) {
        printf("%i ", columnSums[i]);
    }

    printf("\n");

    return 0;
}