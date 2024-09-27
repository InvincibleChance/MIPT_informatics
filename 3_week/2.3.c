#include <stdio.h>
#include <string.h>


void is_palindrome(char w[]) {
    int i = 0;
    int j = strlen(w) - 1;
    while (i < j) {
        if (w[i] != w[j]) {
            printf("No");
            return;
        }
        i += 1;
        j -= 1;
    }
    printf("Yes");
}


int main() {
    char w[111];
    scanf("%s", w);
    is_palindrome(w);
}