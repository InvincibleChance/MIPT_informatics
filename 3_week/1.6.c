#include <stdio.h>
#include <math.h>


const double step = 1e-2;
const double eps = 1e-10;


double gamma(double x) {
    double integral = 0.0;
    double t = 1e-2;
    double S = 1.0;

    while (t < 10000) {
        double f_1 = pow(t, x - 1) * exp(-t);
        double f_2 = pow(t + step, x - 1) * exp(-(t + step));
        S = (f_1 + f_2) / 2 * step;
        integral += S;
        t += step;
    }

    return integral;
}

int main() {
    double x;
    scanf("%lf", &x);
    double result = gamma(x);
    printf("%.10f\n", result);
}