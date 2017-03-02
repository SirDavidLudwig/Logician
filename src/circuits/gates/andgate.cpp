#include "andgate.h"

AndGate::AndGate(QPointF position, Orientation orientation) :
    LogicGate(position, orientation)
{

}

void AndGate::draw(QPainter &painter)
{
    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(QColor("#e64c3c"));
    pen.setWidth(2);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);

    QPainterPath path;
    path.moveTo(pointF(-1, -1));
    path.arcTo(rectF(-1, -1, 2, 2), 90, -180);
    path.lineTo(pointF(-1, 1));
    path.lineTo(pointF(-1, -1));

    painter.drawPath(path);
}
