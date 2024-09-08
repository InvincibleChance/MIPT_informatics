#include <limits.h>
#include <stdio.h>



void function(int n, int counter, int max){
    counter +=1;
    printf("%i ", n);
    if (n==1) {
        printf("\n Length = %i, Max = %i ", counter, max);
        return;
    }
    if (n%2==0) {
        if (n >max) {
            max = n;
        }
        function(n/2, counter, max);
    }
    else if (n%2!=0) {
        if (n >max) {
            max = n;
        }
        function(3*n+1, counter, max);
    }
}


int main() {
    int n;
    int max = INT_MIN;
    int counter = 0;
    scanf("%i", &n);
    function(n, counter, max);
}