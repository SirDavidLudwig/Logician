#include "andgate.h"

AndGate::AndGate(Point position, Orientation orientation) :
    LogicGate(position, orientation)
{
    qDebug() << property("test").toString();
}

void AndGate::draw(QPainter &painter)
{
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen());

    QPainterPath path;
    path.moveTo(pointF(-1, -1));
    path.arcTo(rectF(-1, -1, 2, 2), 90, -180);
    path.lineTo(pointF(-1, 1));
    path.lineTo(pointF(-1, -1));

    painter.drawPath(path);
}
