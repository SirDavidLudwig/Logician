#ifndef VECTOR_H
#define VECTOR_H

#include <QDebug>
#include "point.h"

class Vector : public Point
{
public:
    Vector();
    Vector(Point point);
    Vector(long double x, long double y);

    long double length();

    Vector unitVector();

    Point toPoint();

    void   operator+=(Vector &vector);
    void   operator-=(Vector &vector);
    Vector operator+(Vector &vector);
    Vector operator-(Vector &vector);
    Vector operator*(long double scalar);
    Vector operator/(long double scalar);
    friend QDebug operator<<(QDebug debug, Vector &vector);
};

#endif // VECTOR_H
