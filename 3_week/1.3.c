#include <stdio.h>
#include <limits.h>


float yearfrac(int year, int day) {
    int all;
    if (year % 4 == 0) {
        all = 366;
    } else {
        all = 365;
    }
    return float(day) / all;
}

int main() {
    int n, k;
    float answer;
    scanf("%i %i", &n, &k);
    answer = yearfrac(n, k);
    printf("%f", answer);
}