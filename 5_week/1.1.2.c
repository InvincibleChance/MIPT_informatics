#include <cstdio>
#include <cstdlib>
#include <string.h>

int main() {
    char *p = (char *) malloc(sizeof(char) * 8);
    strcpy(p, "Elephant");
    printf("%s", p);
    free(p);
}