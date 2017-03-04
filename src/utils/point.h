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

    void setX(long double x);
    void setY(long double y);

    long double x();
    long double y();

    QPoint toQPoint();
    QPointF toQPointF();

    void  operator+=(Point &point);
    void  operator-=(Point &point);
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
