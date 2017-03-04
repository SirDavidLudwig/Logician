#include "inputpin.h"

InputPin::InputPin(Point position) :
    CircuitComponent(position, North)
{
}

void InputPin::draw(QPainter &painter)
{
    painter.fillRect(rectF(-0.5, -0.5, 1, 1), painter.pen().color());

    painter.setBrush(QColor("#3b3b3b"));
    painter.drawEllipse(rectF(-0.4, -0.4, 0.8, 0.8));

    QPen pen = painter.pen();
    pen.setColor(QColor("#e64c3c"));
    painter.setPen(pen);

    painter.drawEllipse(rectF(-0.4, -0.4, 0.8, 0.8));
}
