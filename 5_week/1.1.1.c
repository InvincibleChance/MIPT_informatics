#include <cstdio>
#include <cstdlib>


int main() {
    size_t *p = (size_t *) malloc(sizeof(size_t));
    *p = 123;
    printf("%i", *p);
    free(p);
}
