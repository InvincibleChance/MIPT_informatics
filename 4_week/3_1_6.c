#include <stdio.h>

void set_characters(const char *begin, const char *end, char c) {
    char *current = (char *) begin;
    while (current != end) {
        *current = c;
        current++;
    }
}

int main() {
    char s[] = "Sapere Aude";
    set_characters(&s[2], &s[8], 'b');
    printf("%s\n", s); // Напечатает Sabbbbbbude
    set_characters(s, &s[4], 'a');
    printf("%s\n", s); // Напечатает aaaabbbbude
}