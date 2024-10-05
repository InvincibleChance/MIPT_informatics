#include <stdio.h>
#include <math.h>

int solve_quadratic(double a, double b, double c, double *px1, double *px2) {
    const double eps = 1e-10;

    double discriminant = b * b - 4 * a * c;

    if (discriminant < -eps) {
        return 0;
    }

    if (eps < discriminant < eps) {
        *px1 = -b / (2 * a);
        return 1;
    }

    double sqrt_discriminant = sqrt(discriminant);
    *px1 = (-b + sqrt_discriminant) / (2 * a);
    *px2 = (-b - sqrt_discriminant) / (2 * a);
    return 2;
}

int main() {
    double a, b, c;
    double x1, x2;
    int amount_roots;

    printf("Введите коэффициенты a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    amount_roots = solve_quadratic(a, b, c, &x1, &x2);

    if (amount_roots == 0) {
        printf("Корней нет.\n");
    } else if (amount_roots == 1) {
        printf("Один корень: x1 = %.10f\n", x1);
    } else if (amount_roots == 2) {
        printf("Два корня: x1 = %.10f, x2 = %.10f\n", x1, x2);
    }
}