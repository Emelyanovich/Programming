#ifndef POINT_H
#define POINT_H

#include <iostream>

enum coord_system {
    Cartesian,
    Polar
};

struct cartesian_coord {
    double x, y;
};

struct polar_coord {
    double r, phi;
};

class Point {
    double a1, a2;
    coord_system cs;
public:
    Point(double a1 = 0, double a2 = 0, coord_system cs = Cartesian);

    double get_x();
    double get_y();
    double get_r();
    double get_phi();
    void set_x(double x);
    void set_y(double y);
    void set_r(double r);
    void set_phi(double phi);

    friend bool operator== (const Point &p1, const Point &p2);
    friend bool operator!= (const Point &p1, const Point &p2);
    friend std::ostream& operator<< (std::ostream &out, const Point &p);
    friend std::istream& operator>> (std::istream &in, Point &p);
private:
    cartesian_coord to_cartesian(double r, double phi);
    polar_coord to_polar(double x, double y);
};

#endif // POINT_H