#include "xnorgate.h"

XnorGate::XnorGate(QPointF position, Orientation orientation) :
    LogicGate(position, orientation)
{
    addInput(QPoint(-1, -1));
    addInput(QPoint(-1, 1));
    addOutput(QPoint(1, 0));
}

void XnorGate::draw(QPainter &painter)
{
    setBoundingBox(QRectF(-1, -1, 2, 2));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen());

    QPainterPath path;
    path.moveTo(pointF(-1, -1));
    path.quadTo(pointF(-0.5, 0), pointF(-1, 1));

    path.moveTo(pointF(-0.8, -1));
    path.quadTo(pointF(0.5, -1), pointF(0.8, 0));
    path.quadTo(pointF(0.5, 1), pointF(-0.8, 1));
    path.quadTo(pointF(-0.3, 0), pointF(-0.8, -1));

    painter.drawPath(path);
    painter.drawEllipse(rectF(0.80, -0.1, 0.2, 0.2));

    LogicGate::draw(painter);
}
