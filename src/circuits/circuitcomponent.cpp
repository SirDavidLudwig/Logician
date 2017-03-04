#include "circuitcomponent.h"

CircuitComponent::CircuitComponent(Point position, CircuitComponent::Orientation orientation) :
    QObject()
{
    position_ = position;
    orientation_ = orientation;
}

CircuitComponent::Orientation CircuitComponent::orientation() { return orientation_; }
void CircuitComponent::setOrientation(Orientation orientation) { orientation_ = orientation; update(); }

Point CircuitComponent::position() { return position_; }
void CircuitComponent::setPosition(Point position) { position_ = position; update(); }

void CircuitComponent::update() { emit updated(); }

void CircuitComponent::prepareDraw(QPainter &painter, Point position, QSize screen, long double pixelsPerUnit)
{
    viewportPosition_ = position;
    screen_ = screen;
    pixelsPerUnit_ = pixelsPerUnit;

    QTransform transform = painter.transform();

    transform.translate((screen.width()/2) + (position_.x() - viewportPosition_.x())*pixelsPerUnit_ + 1,
                        (screen.height()/2) + (position_.y() - viewportPosition_.y())*pixelsPerUnit_ + 1);

    switch(orientation_) {
        case North:
            transform.rotate(-90);
            break;
        case South:
            transform.rotate(90);
            break;
        case West:
            transform.rotate(180);
            break;
    }

    painter.setTransform(transform);
}

void CircuitComponent::draw(QPainter &painter) { Q_UNUSED(painter); }

QRectF CircuitComponent::rectF(long double x, long double y, long double width, long double height)
{
    return QRectF(pointF(x, y), QSizeF(width*pixelsPerUnit_, height*pixelsPerUnit_));
}

QPointF CircuitComponent::pointF(long double x, long double y)
{
    return QPointF(x * pixelsPerUnit_, y * pixelsPerUnit_);
}
