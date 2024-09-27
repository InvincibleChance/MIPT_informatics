#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *word = argv[1];
    int count = atoi(argv[2]);
    for (int i = 0; i < count; i++) {
        printf("%s", word);
        if (i < count - 1) {
            printf(" ");
        }
    }
}
