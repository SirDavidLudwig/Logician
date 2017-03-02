#include "circuitcomponent.h"

CircuitComponent::CircuitComponent(QPointF position, CircuitComponent::Orientation orientation) :
    QObject()
{
    position_ = position;
    orientation_ = orientation;
}

CircuitComponent::Orientation CircuitComponent::orientation() { return orientation_; }
void CircuitComponent::setOrientation(Orientation orientation) { orientation_ = orientation; update(); }

QPointF CircuitComponent::position() { return position_; }
void CircuitComponent::setPosition(QPointF position) { position_ = position; update(); }

void CircuitComponent::update() { emit updated(); }

void CircuitComponent::prepareDraw(QPointF position, QSize screen, double pixelsPerUnit)
{
    viewportPosition_ = position;
    screen_ = screen;
    pixelsPerUnit_ = pixelsPerUnit;
}

void CircuitComponent::draw(QPainter &painter) { Q_UNUSED(painter); }

QRectF CircuitComponent::rectF(double x, double y, double width, double height)
{
    return QRectF(pointF(x, y), QSizeF(width*pixelsPerUnit_, height*pixelsPerUnit_));
}

QPointF CircuitComponent::pointF(double x, double y)
{
    return QPointF((((x - viewportPosition_.x() + position_.x())*pixelsPerUnit_/screen_.width() + 0.5) * screen_.width()),
                   ((y - viewportPosition_.y() + position_.y())*pixelsPerUnit_/screen_.height() + 0.5) * screen_.height());
}
