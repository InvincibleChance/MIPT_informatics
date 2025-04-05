#include <iostream>
#include <cmath>
using std::cout, std::endl;

struct Vector2f
{
    float x, y;
};

Vector2f operator+(Vector2f left, Vector2f right)
{
    return {left.x + right.x, left.y + right.y};
}

float getDistance(Vector2f a, Vector2f b)
{
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

std::ostream& operator<<(std::ostream& out, Vector2f right)
{
    out << "(" << right.x << ", " << right.y << ")";
    return out;
}


class Shape
{
protected:
    Vector2f mPosition;

public:
    Shape() : mPosition({0, 0}) {}

    Vector2f getPosition() const
    {
        return mPosition;
    }

    void setPosition(Vector2f newPosition)
    {
        mPosition = newPosition;
    }

    void move(Vector2f change)
    {
        mPosition = mPosition + change;
    }

    virtual float calculatePerimeter() const = 0;

    virtual ~Shape() = default;
};


class Circle : public Shape
{
private:
    float mRadius;

public:
    Circle(float radius) : mRadius(radius) {}

    float calculatePerimeter() const override
    {
        return 2 * M_PI * mRadius;
    }
};


class Rectangle : public Shape
{
private:
    float mWidth;
    float mHeight;

public:
    Rectangle(float width, float height) : mWidth(width), mHeight(height) {}

    float calculatePerimeter() const override
    {
        return 2 * (mWidth + mHeight);
    }
};


class Triangle : public Shape
{
private:
    Vector2f mPointA;
    Vector2f mPointB;
    Vector2f mPointC;

public:
    Triangle(Vector2f pointA, Vector2f pointB, Vector2f pointC) :
        mPointA(pointA), mPointB(pointB), mPointC(pointC) {}

    float calculatePerimeter() const override
    {
        return getDistance(mPointA, mPointB) + getDistance(mPointB, mPointC) + getDistance(mPointC, mPointA);
    }
};


int main()
{
    Circle a(10);
    a.setPosition({2, 3});
    cout << "Circle Perimeter: " << a.calculatePerimeter() << endl;
    cout << "Position before move: " << a.getPosition() << endl;
    a.move({5, -1});
    cout << "Position after move: " << a.getPosition() << endl << endl;

    Rectangle b(100, 200);
    b.setPosition({0, 0});
    cout << "Rectangle Perimeter: " << b.calculatePerimeter() << endl;
    cout << "Position before move: " << b.getPosition() << endl;
    b.move({-10, 10});
    cout << "Position after move: " << b.getPosition() << endl << endl;

    Triangle c({5, 2}, {-7, 5}, {4, 4});
    c.setPosition({-3, 4});
    cout << "Triangle Perimeter: " << c.calculatePerimeter() << endl;
    cout << "Position before move: " << c.getPosition() << endl;
    c.move({1, 1});
    cout << "Position after move: " << c.getPosition() << endl;
}