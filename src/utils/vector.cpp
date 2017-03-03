#include "vector.h"

Vector::Vector() : Point() {}
Vector::Vector(Point point) : Point(point.x(), point.y()) {}
Vector::Vector(long double x, long double y) : Point(x, y) {}

long double Vector::length() { return sqrt(x()*x() + y()*y()); }

Vector Vector::unitVector()
{
    if (length() == 0)
        return Vector(0, 0);

    return (*this) / length();
}

Point Vector::toPoint() { return Point(x(), y()); }

Vector Vector::operator+(Vector &vector)       { return Point(x()+vector.x(), y()+vector.y()); }
Vector Vector::operator-(Vector &vector)       { return Point(x()-vector.x(), y()-vector.y()); }
Vector Vector::operator*(long double scalar) { return Point(x()*scalar, y()*scalar); }
Vector Vector::operator/(long double scalar) { return Point(x()/scalar, y()/scalar); }

QDebug operator<<(QDebug debug, Vector &vector)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "Vector(" << (double) vector.x() << ',' << (double) vector.y() << ')';

    return debug;
}
