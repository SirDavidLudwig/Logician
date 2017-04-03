#include "nandgate.h"

NandGate::NandGate(QPointF position, Orientation orientation) :
    LogicGate(position, orientation)
{
    addInput(QPoint(-1, -1));
    addInput(QPoint(-1, 1));
    addOutput(QPoint(1, 0));
}

void NandGate::draw(QPainter &painter)
{
    setBoundingBox(QRectF(-1, -1, 2, 2));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen());

    QPainterPath path;
    path.moveTo(pointF(-1, -1));
    path.arcTo(rectF(-1.2, -1, 2, 2), 90, -180);
    path.lineTo(pointF(-1, 1));
    path.lineTo(pointF(-1, -1));

    painter.drawPath(path);
    painter.drawEllipse(rectF(0.80, -0.1, 0.2, 0.2));

    LogicGate::draw(painter);
}

