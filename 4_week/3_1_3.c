#include <stdio.h>

void cube(float* p) {
    *p = (*p) * (*p) * (*p);
}

int main() {
    float num = 3.0;
    cube(&num);
    printf("%.2f\n", num);
}