#include <stdio.h>
#include <string.h>

int main() {
    char w1[111], w2[111];
    scanf("%s %s", w1, w2);

    int len1 = strlen(w1);
    int len2 = strlen(w2);
    int i = 0, j = 0;

    while (i < len1 || j < len2) {
        if (i < len1) {
            printf("%c", w1[i]);
            i++;
        }
        if (j < len2) {
            printf("%c", w2[j]);
            j++;
        }
    }
    printf("\n");
}