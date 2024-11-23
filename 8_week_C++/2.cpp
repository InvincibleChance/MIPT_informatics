#include <iostream>

using std::cout, std::endl;

using std::cout, std::cin, std::endl;

class Vector2f {
private:
    float x, y;

public:
    Vector2f(float x, float y): x(x), y(y) {
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    Vector2f operator+(const Vector2f &second) const {
        return Vector2f(x + second.x, y + second.y);
    }

    Vector2f operator-(const Vector2f &second) const {
        return Vector2f(x - second.x, y - second.y);
    }

    Vector2f operator*(const Vector2f &second) {
        return Vector2f(second.x * x, second.y * y);
    }

    float operator*(const Vector2f &other) const {
        return x * other.x + y * other.y;
    }

    Vector2f operator-() const {
        return Vector2f(-x, -y);
    }

    Vector2f operator+() const {
        return Vector2f(x, y);
    }

    bool operator==(const Vector2f &outher) const {
        return (x == outher.x) && (y == outher.y);
    }

    bool operator!=(const Vector2f &outher) const {
        return (x != outher.x) || (y != outher.y);
    }

    Vector2f operator+=(const Vector2f &outher) const {
        return Vector2f(x + outher.x, y + outher.y);
    }

    Vector2f operator-=(const Vector2f &outher) const {
        return Vector2f(x - outher.x, y - outher.y);
    }

    Vector2f operator*=(const Vector2f &outher) const {
        return Vector2f(x * outher.x, y * outher.y);
    }

    Vector2f operator/=(float a) const {
        return Vector2f(x / a, y / a);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2f &vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Vector2f &vec) {
        is >> vec.x >> vec.y;
        return is;
    }
};


int main() {
    Vector2f a = {1.0, 2.0};
    Vector2f b = {4.0, -1.0};
    cout << "a = " << a << endl << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "-a = " << -a << endl;
    cout << "Scalar product of a and b = " << a * b << endl;

    cout << "after a/=5;" << (a /= 5) << endl;
    a += b;
    cout << "after a+= b;" << a + b << endl;
}
