#include <stdio.h>

int main() {
    char x;
    scanf("%c", &x);
    if ((x >= 65 && x <= 90) || (x >= 97 && x <= 122)) {
        printf("Letter\n");
    } else if (x >= 48 && x <= 57) {
        printf("Digit\n");
    } else {
        printf("Other\n");
    }
}
