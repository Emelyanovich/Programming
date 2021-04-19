#include "point.h"
#include <math.h>

bool operator== (const Point &p1, const Point &p2) {
    return (abs(p1.a1 - p2.a1) <= pow(10, -10)) &&
           (abs(p1.a2 - p2.a2) <= pow(10, -10));
}

bool operator!= (const Point &p1, const Point &p2) {
    return !(p1 == p2);
}

std::ostream& operator<< (std::ostream &out, const Point &p) {
    out << "(" << p.a1 << "," << p.a2 << ")";
    return out;
}

std::istream& operator>> (std::istream &in, Point &p) {
    std::string x = {};
    in >> x;
    if (x.size() > 4) { //(X,Y)
        size_t comma_pos = x.find(',', 1);
        std::string v1 = x.substr(1, comma_pos-1);
        std::string v2 = x.substr(comma_pos+1, x.size()-2-comma_pos);
        try {
            p.a1 = std::stod(v1);
            p.a2 = std::stod(v2);
        }  catch (...) {
            // do nothing
        }
    }
    return in;
}

cartesian_coord Point::to_cartesian(double r, double phi) {
    return {
        r * cos(phi),
        r * sin(phi)
    };
}

polar_coord Point::to_polar(double x, double y) {
    return {
        hypot(x, y),
        atan2(y, x)
    };
}

double Point::get_x() {
    return (cs == Cartesian) ? a1 : to_cartesian(a1, a2).x;
}

double Point::get_y() {
    return (cs == Cartesian) ? a2 : to_cartesian(a1, a2).y;
}

double Point::get_r() {
    return (cs == Polar) ? a1 : to_polar(a1, a2).r;
}

double Point::Point::get_phi() {
    return (cs == Polar) ? a2 : to_polar(a1, a2).phi;
}

void Point::set_x(double x) {
    if (cs == Cartesian) {
        a1 = x;
    } else {
        polar_coord coord = to_polar(x, to_cartesian(a1, a2).y);
        a1 = coord.r;
        a2 = coord.phi;
    }
}

void Point::set_y(double y) {
    if (cs == Cartesian) {
        a2 = y;
    } else {
        polar_coord coord = to_polar(to_cartesian(a1, a2).x, y);
        a1 = coord.r;
        a2 = coord.phi;
    }
}

void Point::set_r(double r) {
    if (cs == Polar) {
        a1 = r;
    } else {
        cartesian_coord coord = to_cartesian(r, to_polar(a1, a2).phi);
        a1 = coord.x;
        a2 = coord.y;
    }
}

void Point::set_phi(double phi) {
    if (cs == Polar) {
        a2 = phi;
    } else {
        cartesian_coord coord = to_cartesian(to_polar(a1, a2).r, phi);
        a1 = coord.x;
        a2 = coord.y;
    }
}

Point::Point(double a1, double a2, coord_system cs)
    : a1(a1)
    , a2(a2)
    , cs(cs){}
