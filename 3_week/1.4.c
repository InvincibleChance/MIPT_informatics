#include <stdio.h>
#include <math.h>

float find_pi(int n) {
    float pi = 0;
    for (int i = 1; i < n; ++i) {
        pi += 4 * (pow(-1, i + 1)) / (2 * i - 1);
    }
    return pi;
}

int main() {
    int n;
    float answer;
    scanf("%i", &n);
    answer = find_pi(n);
    printf("%f", answer);
}