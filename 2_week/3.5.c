#include <stdio.h>

void binary(int number, char arr[], int *len) {
    if (number > 0) {
        arr[*len] = (number % 2) + '0';
        (*len)++;
        binary(number / 2, arr, len);
    }
}

int main() {
    int number;
    int len = 0;
    char arr[32];
    scanf("%i", &number);
    if (number >= 0) {
        binary(number, arr, &len);
        arr[len] = '\0';
    }
    printf("%s\n", arr);
}