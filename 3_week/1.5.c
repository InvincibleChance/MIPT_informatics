#include <stdio.h>
#include <math.h>

const char *circle(int x_1, int y_1, int r_1, int x_2, int y_2, int r_2) {
    double distance = sqrt(pow(x_2 - x_1, 2) + pow(y_2 - y_1, 2));
    if (distance < r_1 + r_2) {
        return "Intersect";
    }
    if (r_1 + r_2 - 0.00001 < distance && distance < r_1 + r_2 + 0.00001) {
        return "Touch";
    } else {
        return "Do not intersect";
    }
}

int main() {
    int x_1, y_1, r_1, x_2, y_2, r_2;
    scanf("%i %i %i", &x_1, &y_1, &r_1);
    scanf("%i %i %i", &x_2, &y_2, &r_2);
    printf("%s", circle(x_1, y_1, r_1, x_2, y_2, r_2));
}
