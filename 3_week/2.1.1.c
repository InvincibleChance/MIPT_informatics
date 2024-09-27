#include <stdio.h>

int main() {
    char x;

    scanf("%c", &x);

    if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z')) {
        printf("Letter\n");
    } else if (x >= '0' && x <= '9') {
        printf("Digit\n");
    } else {
        printf("Other\n");
    }
}
