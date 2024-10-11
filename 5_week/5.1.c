#include <stdio.h>
#include <stdlib.h>
int a;
void f()
{
    printf("hello f\n");
}
int main() {
    int b;
    static int c;
    int* pi = (int*)malloc(sizeof(int) * 10);
    const char s[] = "cat";
    const char* ps = "dog";
    printf("&pi  = %p\n", &pi);
    printf("pi   = %p\n", pi);
    printf("pi+5 = %p\n", pi + 5);
    printf("&s   = %p\n", &s);
    printf("s    = %p\n", s);
    printf("&ps  = %p\n", &ps);
}