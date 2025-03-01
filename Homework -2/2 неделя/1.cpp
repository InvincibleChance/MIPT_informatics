#include <iostream>

struct Vector2f {
    float x, y;
    Vector2f() : x(0), y(0) {}
    Vector2f(float x, float y) : x(x), y(y) {}

    Vector2f operator+(const Vector2f& other) const {
        return Vector2f(x + other.x, y + other.y);
    }
};

class Shape {
protected:
    Vector2f mPosition;
public:
    Shape(const Vector2f& pos = Vector2f()) : mPosition(pos) {}
    virtual ~Shape() {}

    Vector2f getPosition() const {
        return mPosition;
    }

    void setPosition(const Vector2f& pos) {
        mPosition = pos;
    }

    void move(const Vector2f& change) {
        mPosition = mPosition + change;
    }

    virtual void draw() const = 0;
};

class Circle : public Shape {
private:
    float radius;
public:
    Circle(const Vector2f& pos, float r) : Shape(pos), radius(r) {}

    void draw() const override {
        std::cout << "Circle at (" << mPosition.x << ", " << mPosition.y
                  << ") with radius " << radius << std::endl;
    }
};

class Rectangle : public Shape {
private:
    float width, height;
public:
    Rectangle(const Vector2f& pos, float w, float h) : Shape(pos), width(w), height(h) {}

    void draw() const override {
        std::cout << "Rectangle at (" << mPosition.x << ", " << mPosition.y
                  << ") with width " << width << " and height " << height << std::endl;
    }
};

class Triangle : public Shape {
private:
    float base, height;
public:
    Triangle(const Vector2f& pos, float b, float h) : Shape(pos), base(b), height(h) {}

    void draw() const override {
        std::cout << "Triangle at (" << mPosition.x << ", " << mPosition.y
                  << ") with base " << base << " and height " << height << std::endl;
    }
};

int main() {
    Circle circle(Vector2f(10, 10), 5);
    Rectangle rectangle(Vector2f(20, 20), 10, 5);
    Triangle triangle(Vector2f(30, 30), 8, 6);

    std::cout << "Before moving:" << std::endl;
    circle.draw();
    rectangle.draw();
    triangle.draw();

    Vector2f change(5, -3);


    circle.move(change);
    rectangle.move(change);
    triangle.move(change);

    std::cout << "After moving:" << std::endl;
    circle.draw();
    rectangle.draw();
    triangle.draw();
}