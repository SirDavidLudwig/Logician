#include "circuitview.h"

CircuitView::CircuitView(QWidget *parent, int id) :
    QWidget(parent)
{
    setMouseTracking(false);
    id_ = id;
    active_ = false;
    pixelsPerUnit_ = 1;
    zoom_ = MIN_ZOOM;
}

bool CircuitView::event(QEvent *event)
{
    return this->QWidget::event(event);
}

void CircuitView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF newPos(float(event->pos().x()) / width(), float(event->pos().y()) / height());
    if (event->buttons() & Qt::MiddleButton) {
        setPositionVelocity(mapToCoordinate(mousePos_) - mapToCoordinate(newPos));
    }
    mousePos_ = newPos;
    update();
}

void CircuitView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        dragging_ = true;
        setPositionVelocity(0, 0);
    }
    mousePos_.setX(float(event->pos().x()) / width());
    mousePos_.setY(float(event->pos().y()) / height());
}

void CircuitView::mouseReleaseEvent(QMouseEvent *event) // Execute before the last move event to get the velocity
{
    if (event->button() == Qt::MiddleButton) {
        dragging_ = false;
        QPointF newPos(float(event->pos().x()) / width(), float(event->pos().y()) / height());
        mousePos_.setX(float(event->pos().x()) / width());
        mousePos_.setY(float(event->pos().y()) / height());
    }
}

void CircuitView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (dragging_) {
        translate(positionVelocity(), false);
        setPositionVelocity(0, 0);
    } else {
        if (sqrt(pow(positionVelocity().x(), 2) + pow(positionVelocity().y(), 2)) > 0.001) {
            translate(positionVelocity(), true);
            setPositionVelocity(positionVelocity() - positionVelocity() * MIN_ZOOM * 0.45 / zoom());
        }
    }

    QFont font("Tahoma", 15);
    painter.setFont(font);

    drawGrid(event, painter);

    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    pen.setWidth(10);
    painter.setPen(pen);

    int line = 1;
    QPointF coord = mapToCoordinate(mousePos_);
    painter.drawText(QPoint(5, 20*line++), "Pixels per unit: " + QString::number(pixelsPerUnit()));
    painter.drawText(QPoint(5, 20*line++), "Position(" + QString::number(position().x()) + ", " + QString::number(position().y()) + ")");
    painter.drawText(QPoint(5, 20*line++), "Zoom: " + QString::number(zoom()));


}

void CircuitView::resizeEvent(QResizeEvent *event)
{
    updatePixelsPerUnit();
}

void CircuitView::wheelEvent(QWheelEvent *event)
{
    setZoom(zoom() - zoom() * event->delta() / -1200);
    this->QWidget::wheelEvent(event);
}

void CircuitView::drawGrid(QPaintEvent *event, QPainter &painter)
{
    QPen pen = painter.pen();
    pen.setColor(QColor("#404040"));
    pen.setWidth(1);
    painter.setPen(pen);

    double x = fmod(width()/2 - pixelsPerUnit()*position().x(), pixelsPerUnit());
    double y = fmod(height()/2 - pixelsPerUnit()*position().y(), pixelsPerUnit());

    for (x; x < width(); x += pixelsPerUnit()) {
        painter.drawLine(round(x), 0, round(x), height());
    }

    for (y; y < height(); y += pixelsPerUnit()) {
        painter.drawLine(0, round(y), width(), round(y));
    }
}

QPointF CircuitView::mapToCoordinate(QPointF point) { return mapToCoordinate(point.x(), point.y()); }
QPointF CircuitView::mapToCoordinate(double x, double y)
{
    QPoint pixelPos = toPixels(x - 0.5, y - 0.5);
    QPointF pos;
    pos.setX(float(pixelPos.x()) / pixelsPerUnit() + position().x());
    pos.setY(float(pixelPos.y()) / pixelsPerUnit() + position().y());
    return pos;
}

QPoint CircuitView::toPixels(QPointF point) { return toPixels(point.x(), point.y()); }
QPoint CircuitView::toPixels(double x, double y)
{
    return QPoint(x*width(), y*height());
}

void CircuitView::translate(double x, double y, bool update) { translate(QPointF(x, y), update); }
void CircuitView::translate(QPointF position, bool update) { position_ += position; if(update) this->update(); }

double CircuitView::pixelsPerUnit() { return pixelsPerUnit_; }
void CircuitView::updatePixelsPerUnit() { pixelsPerUnit_ = qMax<float>(width(), height()) / MIN_ZOOM * zoom() / MAX_ZOOM; }

QPointF CircuitView::position() { return position_; }
void CircuitView::setPosition(QPointF position) { setPosition(position.x(), position.y()); }
void CircuitView::setPosition(double x, double y)
{
    position_.setX(x);
    position_.setY(y);
    update();
}

QPointF CircuitView::positionVelocity() { return positionVelocity_; }
void CircuitView::setPositionVelocity(QPointF velocity) { setPositionVelocity(velocity.x(), velocity.y()); }
void CircuitView::setPositionVelocity(double x, double y)
{
    positionVelocity_.setX(x);
    positionVelocity_.setY(y);
}

double CircuitView::zoom() { return zoom_; }
void CircuitView::setZoom(double zoom) { zoom_ = qMin<double>(MAX_ZOOM, qMax<double>(MIN_ZOOM, zoom)); updatePixelsPerUnit(); update(); }

void CircuitView::setActive(bool active) { active_ = active; }
