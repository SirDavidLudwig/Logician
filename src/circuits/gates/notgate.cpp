#include "notgate.h"

NotGate::NotGate(QPointF position, Orientation orientation) :
    LogicGate(position, orientation)
{
    addInput(QPoint(0, 0));
    addOutput(QPoint(1, 0));
}

void NotGate::draw(QPainter &painter)
{
    setBoundingBox(QRectF(0, -0.5, 1, 1));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen());

    QPainterPath path;
    path.moveTo(pointF(0, -0.5));
    path.lineTo(pointF(0.80, 0));
    path.lineTo(pointF(0, 0.5));
    path.lineTo(pointF(0, -0.5));

    painter.drawPath(path);
    painter.drawEllipse(rectF(0.80, -0.1, 0.2, 0.2));

    LogicGate::draw(painter);
}
