#include "circuitview.h"

CircuitView::CircuitView(QWidget *parent) : QWidget(parent)
{
    setObjectName("CircuitView");
}

void CircuitView::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QColor("#404040"));
    for (int x = 10; x < width(); x += 25)
        painter.drawLine(x, 0, x, height());

    for (int y = 10; y < height(); y += 25)
        painter.drawLine(0, y, width(), y);
}
