#include <stdio.h>
#include <string.h>

void safe_strcpy(char dest[], size_t max_size, const char src[]) {
    if (max_size == 0) {
        return;
    }
    size_t i;
    for (i = 0; i < max_size - 1 && src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

int main() {
    char a[10] = "Mouse";
    char b[50] = "LargeElephant";
    safe_strcpy(a, sizeof(a), b);
    printf("%s\n", a);
}