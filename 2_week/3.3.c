#include <stdio.h>


void print_even(int s, int e) {
    for (int i = s; i < e + 1; ++i) {
        if (i % 2 == 0) {
            printf("%i ", i);
        }
    }
}

int main() {
    int s;
    int e;
    scanf("%i %i", &s, &e);
    print_even(s, e);
}
