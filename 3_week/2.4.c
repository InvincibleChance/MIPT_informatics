#include <stdio.h>
#include <ctype.h>
#include <string.h>


void cesar(char *str, int k) {
    int i = 0;
    while (i < strlen(str)) {
        char ch;
        ch = str[i];
        if (isalpha(ch)) {
            if (isupper(ch)) {
                if (ch + k < 90) {
                    str[i] = ch + k;
                    i += 1;
                }
                if (ch + k >= 90) {
                    str[i] = ch - 90 + k + 65 - 1;
                    i += 1;
                }
            } else if (islower(ch)) {
                if (ch + k <= 122) {
                    str[i] = ch + k;
                    i += 1;
                }
                if (ch + k > 122) {
                    str[i] = (-122 + ch + k) + 97 - 1;
                    i += 1;
                }
            }
        }
    }
}

int main() {
    char str[256];
    int k;
    scanf("%i", &k);
    scanf(" %[^\n]", str);

    char *word = strtok(str, " ");

    while (word != NULL) {
        cesar(word, k);
        printf("%s ", word);
        word = strtok(NULL, " ");
    }
}