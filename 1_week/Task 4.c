#include <stdio.h>
#include <limits.h>

// Находим минимум
int find_min(int n) {
    int min = INT_MAX;
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%i", &a);
        if (a < min) {
            min = a;
        }
    }
    return min;
}

// Минимальное четное и макс нечетное
void find_min_even_max_odd(int n) {
    int min_even = INT_MAX;
    int max_odd = INT_MIN;
    int even = 0;
    int odd = 0;

    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%i", &a);
        if (a%2 == 0) {
            even =1;
            if (a < min_even){
                min_even = a;
            }
        }else {
                odd +=1;
                if (a > max_odd) {
                    max_odd = a;
                }
            }
        }
    if (!even) {
        printf(" None ");
    }
    if (!odd) {
        printf(" None ");
    }
    if (even) {
        printf(" %i", min_even);
    }
    if (odd) {
        printf("%i", max_odd);
    }

}

// Находим максимум и количество элементов равных ему
void find_max_and_count(int n) {
    int max = INT_MIN;
    int count = 0;
    for (int i =0; i<n;++i) {
        int a;
        scanf("%i", &a);
        if (a>max) {
            max = a;
            count = 1;
        }
        else {
            count +=1;
        }
    }
    printf("%i %i", max, count);
}
// Последовательности
void sequence(int n) {
    int increse = 1;
    int decrease = 1;
    int equal = 1;
    int prevue;
    int currently;

    scanf("%i", &prevue);


    for (int i =1;i<n; ++i) {
        scanf("%i", &currently);
        if (prevue>currently || prevue == currently) {
            increse = 0;
        }
        if (prevue<currently || prevue == currently) {
            decrease = 0;
        }
        if (prevue!=currently) {
            equal = 0;
        }
    }
    if (increse) {
        printf("Increasing");
    }
    else if (decrease) {
        printf("Decreasing");
    }
    else if (equal) {
        printf("Equal");
    }
    else {
        printf("None");
    }
    prevue = currently;
}



int main(){
    int n;
    printf("Введите числа для нахождения минимума");
    scanf("%i", &n);
    printf("Минимум = %i\n", find_min(n));
    printf("Введите числа для нахождения максимального четного и минимального нечетного:");
    scanf("%i", &n);
    find_min_even_max_odd(n);
    printf("Введите числа для нахождения количества вхождения максимума:");
    scanf("%i", &n);
    find_max_and_count(n);
    printf("Введите числа для последовательности:");
    scanf("%i", &n);
    sequence(n);

}
