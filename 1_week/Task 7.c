#include <stdio.h>

int main() {
    int n, m;
    int sum = 0;

    scanf("%d %d", &n, &m);


    for (int i =1;i<n+1;++i) {
        for (int j=1;j<m+1;++j) {
            if ((i+j)%2 ==0) {
                sum += i*j;
            }
            else {
                sum -= i*j;
            }
        }
    }
    printf("%d\n", sum);

    return 0;
}
