#include "point.h"

Point::Point() : Point(0, 0) {}
Point::Point(long double x, long double y)
{
    x_ = x;
    y_ = y;
}

long double Point::dot(Point point)
{
    return x()*point.x() + y()*point.y();
}

long double Point::x() { return x_; }
long double Point::y() { return y_; }

QPoint  Point::toQPoint()  { return QPoint(round(x()), round(y())); }
QPointF Point::toQPointF() { return QPointF(x(), y()); }

Point Point::operator+(Point &point)       { return Point(x()+point.x(), y()+point.y()); }
Point Point::operator-(Point &point)       { return Point(x()-point.x(), y()-point.y()); }
Point Point::operator*(long double scalar) { return Point(x()*scalar, y()*scalar); }
Point Point::operator/(long double scalar) { return Point(x()/scalar, y()/scalar); }

QDebug operator<<(QDebug debug, Point &point)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "Point(" << (double) point.x() << ',' << (double) point.y() << ')';

    return debug;
}
