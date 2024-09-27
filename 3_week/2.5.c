#include <stdio.h>


void trim_after_first_space(char str[]) {
    char *s = str;
    while (*s != '\0' && *s != ' ') {
        s += 1;
    }
    if (*s == ' ') {
        *s = '\0';
    }
}


int main() {
    char a[] = "Cats and Dogs";
    printf("%s\n", a); // Должно напечатать Cats and Dogs
    trim_after_first_space(a);
    printf("%s\n", a); // Должно напечатать Cats
}