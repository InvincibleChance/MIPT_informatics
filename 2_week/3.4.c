#include <stdio.h>


int sum_of_digits(int n) {
    int answer = 0;
    while (n != 0) {
        answer += n % 10;
        n /= 10;
    }
    printf("%i\n", answer);
}


void sum_of_digits_rec(int n, int answerr) {
    if (n == 0) {
        printf("%i", answerr);
    }
    if (n > 0) { sum_of_digits_rec(n / 10, answerr += (n % 10)); }
}

int main() {
    int number;
    int answerr = 0;
    scanf("%i", &number);
    sum_of_digits(number);
    sum_of_digits_rec(number, answerr);
}
