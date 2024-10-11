#include <cstdio>
#include <cstdlib>
#include <string.h>

int main() {
    char **str = (char **) malloc(sizeof(char *));
    *str = (char *)malloc(20 * sizeof(char));
    strcpy(*str, "Cats and Dogs");
    printf("%s", *str);
    free(*str);
    free(str);
}