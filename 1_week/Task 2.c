#include <stdio.h>


int main() {
    int a;
    int b;
    int c;
    int check = 100;
    scanf("%i %i %i", &a, &b, &c);

    if (a+1==b && b+1 ==c || a-1==b && b-1 ==c ) {
        printf("Consecutive ");
        check -=1;
    }
    if (a < b && b< c) {
        printf("Increasing ");
        check -=1;
    }
    if (a > b && b>c) {
        printf("Decreasing ");
        check -=1;
    }
    if (a == b && b==c) {
        printf("Equal ");
        check -=1;
    }
    if (check ==100) {
        printf("None");
    }
}
