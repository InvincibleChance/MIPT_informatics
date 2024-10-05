#include <stdio.h>
#include <math.h>

struct point {
    double x;
    double y;
};

typedef struct point Point;
typedef struct triangle Triangle;


struct triangle {
    Point a;
    Point b;
    Point c;
};


void print_point(Point p) {
    printf("(%.2f, %.2f)", p.x, p.y);
}

void print_triangle(const Triangle *t) {
    printf("{");
    print_point(t->a);
    printf(", ");
    print_point(t->b);
    printf(", ");
    print_point(t->c);
    printf("}\n");
}


double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}


double get_triangle_perimeter(const Triangle *t) {
    double ab = distance(t->a, t->b);
    double bc = distance(t->b, t->c);
    double ca = distance(t->c, t->a);
    return ab + bc + ca;
}


Triangle moved_triangle(const Triangle *t, Point vector) {
    Triangle new_triangle;
    new_triangle.a.x = t->a.x + vector.x;
    new_triangle.a.y = t->a.y + vector.y;
    new_triangle.b.x = t->b.x + vector.x;
    new_triangle.b.y = t->b.y + vector.y;
    new_triangle.c.x = t->c.x + vector.x;
    new_triangle.c.y = t->c.y + vector.y;
    return new_triangle;
}


void move_triangle(Triangle *t, Point vector) {
    t->a.x += vector.x;
    t->a.y += vector.y;
    t->b.x += vector.x;
    t->b.y += vector.y;
    t->c.x += vector.x;
    t->c.y += vector.y;
}

int main() {
    Triangle t = {{1.00, 0.00}, {0.50, 2.00}, {0.00, 1.50}};
    Point d = {10.0, 1.0};
    Point d_1 = {1.3, 1.3};
    printf("Печатаем точку:");
    print_point(d);
    printf("\n");
    printf("Печатаем треугольник:");
    print_triangle(&t);
    printf("Расстояние между точками: ");
    printf("%.2f\n", distance(d, d_1));
    printf("Периметр треугольника %.2f\n", get_triangle_perimeter(&t));
    Triangle new_triangle = moved_triangle(&t, d);
    printf("Перемещенный треугольник: ");
    print_triangle(&new_triangle);
    printf("Измененный треугольник: ");
    move_triangle(&t, d);
    print_triangle(&t);
}