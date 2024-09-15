#include <stdio.h>

void sortColumn(int column[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (column[j] > column[j + 1]) {
                int temp = column[j];
                column[j] = column[j + 1];
                column[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int matrix[n * m];
    for (int i = 0; i < n * m; ++i) {
        scanf("%d", &matrix[i]);
    }
    int column[n];

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            column[i] = matrix[i * m + j];
        }

        sortColumn(column, n);

        for (int i = 0; i < n; ++i) {
            matrix[i * m + j] = column[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%i ", matrix[i * m + j]);
        }
        printf("\n");
    }
}