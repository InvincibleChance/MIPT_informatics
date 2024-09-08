#include <stdio.h>

int main() {
    int a;
    int b;
    int c;
    scanf("%i %i %i", &a, &b, &c);
    for (int i =c;i<b+1;i+=c) {
        printf("%i\n", i);
    }
}