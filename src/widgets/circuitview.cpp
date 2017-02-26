#include "circuitview.h"

CircuitView::CircuitView(QWidget *parent, int id) :
    QWidget(parent)
{
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::TapGesture);
    setMouseTracking(false);
    id_ = id;
    active_ = false;
    dragging_ = false;
    touchDragging_ = false;
    pixelsPerUnit_ = 1;
    zoom_ = MIN_ZOOM;
}

bool CircuitView::event(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin ||
        event->type() == QEvent::TouchUpdate ||
        event->type() == QEvent::TouchEnd ||
        event->type() == QEvent::TouchCancel)
    {
        QTouchEvent *touch = (QTouchEvent*) event;
        if (touch->touchPoints().length() == 2) {
            touchDragging_ = true;
            QTouchEvent::TouchPoint pointA = touch->touchPoints()[0];
            QTouchEvent::TouchPoint pointB = touch->touchPoints()[1];

            QPointF lastHotSpot = toScreen(pointA.lastPos() + pointB.lastPos()) / 2;
            QPointF newHotSpot = toScreen(pointA.pos() + pointB.pos()) / 2;
            mousePos_ = lastHotSpot;

            QPointF lastA = toScreen(pointA.lastPos());
            QPointF lastB = toScreen(pointB.lastPos());

            QPointF newA = toScreen(pointA.pos());
            QPointF newB = toScreen(pointB.pos());

            if (pointA.state() != Qt::TouchPointReleased && pointB.state() != Qt::TouchPointReleased) {
                setZoom(lastA, lastB, newA, newB, false);
                setPositionVelocity(mapToCoordinate(mousePos_) - mapToCoordinate(newHotSpot));
                mousePos_ = newHotSpot;
                repaint();
            } else {
                touchDragging_ = false;
                setPositionVelocity(lastPositionVelocity_);
                mousePos_.setX(newHotSpot.x());
                mousePos_.setY(newHotSpot.y());
                repaint();
            }
       } else {
            touchDragging_ = false;
       }
    } else

        return this->QWidget::event(event);
}

void CircuitView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF newPos = toScreen(event->pos());
    if (event->buttons() & Qt::RightButton) {
        setPositionVelocity(mapToCoordinate(mousePos_) - mapToCoordinate(newPos));
        mousePos_ = newPos;
        update();
    }
}

void CircuitView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        dragging_ = true;
        setPositionVelocity(0, 0);
    }
    mousePos_.setX(double(event->pos().x()) / width());
    mousePos_.setY(double(event->pos().y()) / height());
}

void CircuitView::mouseReleaseEvent(QMouseEvent *event) // Execute before the last move event to get the velocity
{
    if (event->button() == Qt::RightButton) {
        dragging_ = false;
        mousePos_.setX(double(event->pos().x()) / width());
        mousePos_.setY(double(event->pos().y()) / height());
    }
}

void CircuitView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (dragging_ || touchDragging_) {
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
    int direction = event->angleDelta().y() / -abs(event->angleDelta().y());
    setZoom(zoom() - zoom() * 0.1 * direction, toScreen(event->pos()));
    this->QWidget::wheelEvent(event);
}

void CircuitView::drawGrid(QPaintEvent *event, QPainter &painter)
{
    QPen pen = painter.pen();
    pen.setColor(QColor("#404040"));
    pen.setWidth(1);
    painter.setPen(pen);

    double x = dmod(double(width()/2.0) - pixelsPerUnit()*position().x(), pixelsPerUnit());
    double y = dmod(double(height()/2.0) - pixelsPerUnit()*position().y(), pixelsPerUnit());
    for (x; x < width(); x += pixelsPerUnit()) {
        painter.drawLine(round(x), 0, round(x), height());
    }

    for (y; y < height(); y += pixelsPerUnit()) {
        painter.drawLine(0, round(y), width(), round(y));
    }
}

void CircuitView::drag()
{

}

QPointF CircuitView::mapFromCoordinate(QPointF point) { return mapFromCoordinate(point.x(), point.y()); }
QPointF CircuitView::mapFromCoordinate(double x, double y)
{
    QPointF coord;
    coord.setX((x - position().x()) * pixelsPerUnit() + 0.5);
    coord.setY((y - position().y()) * pixelsPerUnit() + 0.5);
    return coord;
}

QPointF CircuitView::mapToCoordinate(QPointF point) { return mapToCoordinate(point.x(), point.y()); }
QPointF CircuitView::mapToCoordinate(double x, double y)
{
    QPointF pos;
    pos.setX((x - 0.5)*width() / pixelsPerUnit() + position().x());
    pos.setY((y - 0.5)*height() / pixelsPerUnit() + position().y());
    return pos;
}

QPointF CircuitView::toScreen(QPoint point) { return toScreen(point.x(), point.y()); }
QPointF CircuitView::toScreen(QPointF point) { return toScreen(point.x(), point.y()); }
QPointF CircuitView::toScreen(double x, double y) {
    return QPointF(x/width(), y/height());
}

QPoint CircuitView::toPixels(QPointF point) { return toPixels(point.x(), point.y()); }
QPoint CircuitView::toPixels(double x, double y)
{
    return QPoint(x*width(), y*height());
}

// fmod was returning broken results...
double CircuitView::dmod(double x, double y) { return x - floor(x/y)*y; }
double CircuitView::magnitude(QPoint point) { return magnitude(QPointF(point.x(), point.y())); }
double CircuitView::magnitude(QPointF point) { return sqrt(pow(point.x(), 2) + pow(point.y(), 2)); }

void CircuitView::translate(double x, double y, bool update) { translate(QPointF(x, y), update); }
void CircuitView::translate(QPointF position, bool update) { position_ += position; if(update) this->update(); }

double CircuitView::pixelsPerUnit() { return pixelsPerUnit_; }
void CircuitView::updatePixelsPerUnit() { pixelsPerUnit_ = qMax<double>(width(), height()) / MIN_ZOOM * zoom() / MAX_ZOOM; }

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
    lastPositionVelocity_.setX(positionVelocity_.x());
    lastPositionVelocity_.setY(positionVelocity_.y());
    positionVelocity_.setX(x);
    positionVelocity_.setY(y);
}

double CircuitView::zoom() { return zoom_; }
void CircuitView::setZoom(double zoom, bool update) { setZoom(zoom, mapToCoordinate(QPointF(0.5, 0.5)), update); }
void CircuitView::setZoom(double zoom, QPointF point, bool update)
{
    QPointF coord = mapToCoordinate(point);
    zoom_ = qMin<double>(MAX_ZOOM, qMax<double>(MIN_ZOOM, zoom));
    updatePixelsPerUnit();

    setPosition(coord - QPointF(width()*(point.x()-0.5)/pixelsPerUnit(), height()*(point.y()-0.5)/pixelsPerUnit()));

    if (update)
        repaint();

}
void CircuitView::setZoom(QPointF pointAi, QPointF pointBi, QPointF pointAf, QPointF pointBf, bool update)
{
    QPointF hotSpot = (pointAf + pointBf)/2;

    QPointF a(width()*(pointAi.x() - pointBi.x()), height()*(pointAi.y() - pointBi.y()));
    QPointF b(width()*(pointAf.x() - pointBf.x()), height()*(pointAf.y() - pointBf.y()));

    double newZoom = zoom() * magnitude(b) / magnitude(a);
    setZoom(newZoom, hotSpot, update);
}

void CircuitView::setActive(bool active) { active_ = active; }
