#include <iostream>
#include "point.hpp"


using std::cout, std::endl;

class Circle {
private:
    Point center;
    float radius;

public:
    void Center(const Point &center) {
        this->center = center;
    }

    void Radius(float radius) {
        this->radius = radius;
    }

    Circle(const Point &center, float radius) {
        Center(center);
        Radius(radius);
    }

    Circle() {
        center = Point(0, 0);
        radius = 1.0f;
    }

    Circle(const Circle &circle) {
        Center(circle.center);
        Radius(circle.radius);
    }

    void setCenter(const Point &center) {
        this->center = center;
    }

    void setRadius(float radius) {
        if (radius < 0) {
            this->radius = 0;
        } else {
            this->radius = radius;
        }
    }

    Point getCenter() const {
        return center;
    }

    float getRadius() const {
        return radius;
    }

    float area() const {
        return 3.14 * radius * radius;
    }

    float distance(const Point &p) const {
        float dist_to_center = center.distance(p);
        return std::max(0.0f, dist_to_center - radius);
    }

    bool isColliding(const Circle &c) const {
        float dist_between = center.distance(c.center);
        return dist_between <= (radius + c.radius);
    }

    void move(const Point &p) {
        center = Point(center.getX() + p.getX(), center.getY() + p.getY());
    }
};

int main() {
    Point p = {7, -1};
    Point q = {-4, 2};
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "p + q = " << p + q << endl;

    Circle a({4, 1}, 3);
    Circle b;

    cout << "Circle a: center: " << a.getCenter() << " radius: " << a.getRadius() << endl;
    cout << "Circle b: center: " << b.getCenter() << " radius: " << b.getRadius() << endl;

    cout << "Area of a = " << a.area() << endl;
    cout << "Distance from point p to circle a = " << a.distance(p) << endl;


    cout << "Collisions:" << endl;
    if (a.isColliding(b))
        cout << "Yes, a is colliding b" << endl;
    else
        cout << "No, a isn't colliding b" << endl;


    cout << "Moving b by {1, 1}:" << endl;
    b.move({1, 1});
    if (a.isColliding(b))
        cout << "Yes, a is colliding b" << endl;
    else
        cout << "No, a isn't colliding b" << endl;
}
