#ifndef POINT_H
#define POINT_H

#include <QDebug>
#include <QPoint>
#include <QPointF>

class Point
{
public:
    Point();
    Point(long double x, long double y);

    long double dot(Point point);

    long double x();
    long double y();

    QPoint toQPoint();
    QPointF toQPointF();

    Point operator+(Point &point);
    Point operator-(Point &point);
    Point operator*(long double scalar);
    Point operator/(long double scalar);
    friend QDebug operator<<(QDebug debug, Point &point);

private:
    long double x_;
    long double y_;

};

#endif // POINT_H
