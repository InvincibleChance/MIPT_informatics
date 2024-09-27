#include <stdio.h>
#include <ctype.h>

int main() {
    char x;
    scanf("%c", &x);
    if (isalpha(x)) {
        printf("Letter\n");
    } else if (isdigit(x)) {
        printf("Digit\n");
    } else {
        printf("Other\n");
    }
}