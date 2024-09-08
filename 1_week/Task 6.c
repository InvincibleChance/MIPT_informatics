#include <limits.h>
#include <stdio.h>



void function(int n, int *counter, int *max){
    (*counter) ++;
    // printf("%i ", n);
    if (n==1) {
        // printf("\n Length = %i, Max = %i ", counter, max);
        return;
    }
    if (n%2==0) {
        if (n >*max) {
            *max = n;
        }
        function(n/2, counter, max);
    }
    else if (n%2!=0) {
        if (n >*max) {
            *max = n;
        }
        function(3*n+1, counter, max);
    }
}


int main() {
    int a;
    int b;
    int n_number = -1;
    int max_sequence = -1;
    scanf("%i %i", &a, &b);
    for (int i = a;i<b+1;++i) {
        int max = INT_MIN;
        int counter = 0;
        function(i, &counter, &max);
        if (max_sequence < counter) {
            max_sequence = counter;
            n_number = i;
        }
    }
    printf("%i %i", n_number, max_sequence);
}