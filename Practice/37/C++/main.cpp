#include <iostream>
#include <cmath>
using namespace std;

double sqr(double a);
bool equal(double a, double b, double e = 1E-10);

const auto PI = 3.141592653589793;
const double PRECISION = 1e+10;

enum coord_sys {
    Cartesian,
    Polar
};

class Point {
private:
    double x, y;

public:
    Point(double a1 = 0, double a2 = 0, coord_sys coord_system = Cartesian) {
        if (coord_system == Cartesian) {
            x = a1;
            y = a2;
            return;
        }
        else {
            x = cos(a2) * a1;
            y = sin(a2) * a1;
        }
    }

    bool operator==(const Point &p) const {
        return((trunc(x * PRECISION) / PRECISION) == (trunc(p.x * PRECISION) / PRECISION) and
               (trunc(y * PRECISION) / PRECISION) == (trunc(p.y * PRECISION) / PRECISION));
    }

    bool operator!=(const Point &p) {
        return((trunc(x * PRECISION) / PRECISION) != (trunc(p.x * PRECISION) / PRECISION) and
               (trunc(y * PRECISION) / PRECISION) != (trunc(p.y * PRECISION) / PRECISION));
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p);
    friend std::istream& operator>>(std::istream& in, Point& p);

    double get_x() const {
        return x;
    }

    double get_y() const {
        return y;
    }

    double get_r() const {
        return sqrt(x * x + y * y);
    }

    double get_phi() const {
        return atan(y / x) + (x < 0 ? PI : 0);
    }

    void set_x(double x) {
        this->x = x;
    }

    void set_y(double y) {
        this->y = y;
    }

    void set_r(double r) {
        double phi = get_phi();
        this->x = cos(phi) * r;
        this->y = sin(phi) * r;
    }

    void set_phi(double phi) {
        double r = get_r();
        this->x = cos(phi) * r;
        this->y = sin(phi) * r;
    }
};

std::ostream& operator<<(std::ostream& out, const Point& p) {
    return out << '(' << p.get_x() << ',' << p.get_y() << ')';
}

std::istream& operator>>(std::istream& in, Point& p) {
    double sym;
    in.ignore(1);
    in >> sym;
    p.set_x(sym);
    in.ignore(1);
    in >> sym;
    p.set_y(sym);
    in.ignore(1);
    return in;
}

class Vector
{
private:
    Point point;

public:
    Vector() : point(1, 0) {
    }

    Vector(const Point& end) : point(end.get_x(), end.get_y()) {
    }

    Vector(const Point& begin, const Point& end) : point(end.get_x() - begin.get_x(), end.get_y() - begin.get_y()) {
    }

    bool operator ==(const Vector& v) const {
        return point == v.point;
    }

    Vector operator -() const {
        Point p = point;
        p.set_x(-p.get_x());
        p.set_y(-p.get_y());

        return Vector(p);
    }

    Vector operator -(const Vector& v) const {
        Point p;
        p.set_x(point.get_x() - v.point.get_x());
        p.set_y(point.get_y() - v.point.get_y());

        return Vector(p);
    }

    Vector operator +(const Vector& v) const {
        Point p;
        p.set_x(point.get_x() + v.point.get_x());
        p.set_y(point.get_y() + v.point.get_y());

        return Vector(p);
    }

    Vector operator *(double mul) const {
        Point p = point;
        p.set_x(p.get_x() * mul);
        p.set_y(p.get_y() * mul);
        return Vector(p);
    }

    double operator *(const Vector& v) const {
        return length() * v.length() * cos(point.get_phi() - v.point.get_phi());
    }

    double length() const {
        return point.get_r();
    }
};

int main()
{
    Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));
    if (a == b && b == a) cout << "Equality test passed\n";
    else cout << "Equality test failed\n";

    Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
    if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
    else cout << "Invert test failed\n";

    if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
    else cout << "Summation test failed\n";

    if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
    else cout << "Subtraction test failed\n";

    if (ox * 3 == ox + ox + ox &&
        oy * 3 == oy + oy + oy &&
        ox * (-3) == -ox - ox - ox &&
        oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
    else cout << "Multiplication by number test failed\n";

    if (equal(ox.length(), 1) &&
        equal(oy.length(), 1) &&
        equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
    else cout << "Length test failed\n";

    if (equal(ox*ox, sqr(ox.length())) &&
        equal(oy*oy, sqr(oy.length())) &&
        equal((ox*3 + oy*4)*(ox*3 + oy*4), sqr((ox*3 + oy*4).length()))) cout << "Multiplication by Vector test passed\n";
    else cout << "Multiplication by Vector test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

double sqr(double a) {
    return a * a;
}