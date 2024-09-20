#include <stdio.h>

unsigned long trib(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }

    unsigned long Trib[n + 1];
    Trib[0] = 0;
    Trib[1] = 0;
    Trib[2] = 1;


    for (int i = 3; i <= n; ++i) {
        Trib[i] = Trib[i - 3] + Trib[i - 2] + Trib[i - 1];
    }
    return Trib[n];
}

int main() {
    int n;
    scanf("%i", &n);
    trib(n);
    printf("%i", trib(n));
}