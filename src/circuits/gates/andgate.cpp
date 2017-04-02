#include "andgate.h"

AndGate::AndGate(QPointF position, Orientation orientation) :
    LogicGate(position, orientation)
{
    addInput(QPoint(-2, -1));
    addInput(QPoint(-2, 1));
    addOutput(QPoint(0, 1));
}

void AndGate::draw(QPainter &painter)
{
    setBoundingBox(QRectF(-2, -1, 3, 2));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen());

    QPainterPath path;
    path.moveTo(pointF(-1, -1));
    path.arcTo(rectF(-1, -1, 2, 2), 90, -180);
    path.lineTo(pointF(-1, 1));
    path.lineTo(pointF(-1, -1));

    painter.drawPath(path);

    LogicGate::draw(painter);
}
