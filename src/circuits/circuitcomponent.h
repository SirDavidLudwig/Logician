#ifndef CIRCUITENTITY_H
#define CIRCUITENTITY_H

#include <QColor>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QSize>

#include "../utils/point.h"

class CircuitComponent : public QObject
{
    Q_OBJECT
public:

    static const QColor COLOR_DEFAULT;
    static const QColor COLOR_SELECTED;

    enum Orientation {
        North,
        East,
        South,
        West
    };

    CircuitComponent(Point position = Point(0, 0), Orientation orientation = North);

    bool isSelected();
    void setSelected(bool selected);

    Point position();
    Orientation orientation();

    QRectF rectF(long double x, long double y, long double width, long double height);
    QPointF pointF(long double x, long double y);

    QPen pen();

private:
    bool selected_;
    Orientation orientation_;
    Point position_;

    long double pixelsPerUnit_;
    Point viewportPosition_;
    QSize screen_;

signals:
    void updated();

public slots:
    void setPosition(Point position);
    void setOrientation(Orientation orientation);

    virtual void draw(QPainter &painter);
    void prepareDraw(QPainter &painter, Point position, QSize screen, long double pixelsPerUnit);
    void update();

};

#endif // CIRCUITENTITY_H
