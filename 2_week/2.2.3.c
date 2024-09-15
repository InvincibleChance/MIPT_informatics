#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int matrix_1[n][n];
    int matrix_2[n][n];
    int answer_matrix[n][n] = {0};

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix_1[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix_2[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                answer_matrix[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%i ", answer_matrix[i][j]);
        }
        printf("\n");
    }
}