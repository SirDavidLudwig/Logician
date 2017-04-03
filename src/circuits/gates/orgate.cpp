#include "orgate.h"

OrGate::OrGate(QPointF position, Orientation orientation) :
    LogicGate(position, orientation)
{
    addInput(QPoint(-1, -1));
    addInput(QPoint(-1, 1));
    addOutput(QPoint(1, 0));
}

void OrGate::draw(QPainter &painter)
{
    setBoundingBox(QRectF(-1, -1, 2, 2));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen());

    QPainterPath path;
    path.moveTo(pointF(-1, -1));
    path.quadTo(pointF(0.5, -1), pointF(1, 0));
    path.quadTo(pointF(0.5, 1), pointF(-1, 1));
    path.quadTo(pointF(-0.5, 0), pointF(-1, -1));

    painter.drawPath(path);

    LogicGate::draw(painter);
}
