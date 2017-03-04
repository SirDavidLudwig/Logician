#include "circuitview.h"

CircuitView::CircuitView(QWidget *parent, Circuit *circuit) :
    QWidget(parent)
{
    setMouseTracking(false);
    active_ = false;
    circuit_ = NULL;
    dragging_ = false;
    touchDragging_ = false;
    pixelsPerUnit_ = 1;
    zoom_ = MIN_ZOOM;

    setCircuit(circuit);
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

            Point lastHotSpot = toScreen(pointA.lastPos() + pointB.lastPos()) / 2;
            Point newHotSpot = toScreen(pointA.pos() + pointB.pos()) / 2;
            mousePos_ = lastHotSpot;

            Point lastA = toScreen(pointA.lastPos());
            Point lastB = toScreen(pointB.lastPos());

            Point newA = toScreen(pointA.pos());
            Point newB = toScreen(pointB.pos());

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
    }

    return this->QWidget::event(event);
}

void CircuitView::mouseMoveEvent(QMouseEvent *event)
{
    Point newPos = toScreen(event->pos());
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
    mousePos_.setX(long double(event->pos().x()) / width());
    mousePos_.setY(long double(event->pos().y()) / height());
}

void CircuitView::mouseReleaseEvent(QMouseEvent *event) // Execute before the last move event to get the velocity
{
    if (event->button() == Qt::RightButton) {
        dragging_ = false;
        mousePos_.setX(long double(event->pos().x()) / width());
        mousePos_.setY(long double(event->pos().y()) / height());
    }
}

void CircuitView::paintEvent(QPaintEvent *event)
{
    QPainter painter;

    painter.begin(this);

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
    drawComponents(event, painter);

    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    pen.setWidth(10);
    painter.setPen(pen);

    int line = 1;
    Point coord = mapToCoordinate(mousePos_);
    painter.drawText(QPoint(5, 20*line++), "Pixels per unit: " + QString::number((double)pixelsPerUnit()));
    painter.drawText(QPoint(5, 20*line++), "Position(" + QString::number((double)position().x()) + ", " + QString::number((double)position().y()) + ")");
    painter.drawText(QPoint(5, 20*line++), "Zoom: " + QString::number((double)zoom()));

    painter.end();
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

    long double x = dmod(long double(width()/2.0) - pixelsPerUnit()*position().x(), pixelsPerUnit());
    long double y = dmod(long double(height()/2.0) - pixelsPerUnit()*position().y(), pixelsPerUnit());
    for (x; x < width(); x += pixelsPerUnit()) {
        painter.drawLine(round(x), 0, round(x), height());
    }

    for (y; y < height(); y += pixelsPerUnit()) {
        painter.drawLine(0, round(y), width(), round(y));
    }
}

void CircuitView::drawComponents(QPaintEvent *event, QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);

    QTransform transform = painter.transform();

    foreach(CircuitComponent *component, circuit()->components()) {
        component->prepareDraw(painter, position(), size(), pixelsPerUnit_);
        component->draw(painter);
        painter.setTransform(transform);
    }
}

bool CircuitView::isActive() { return active_; }
void CircuitView::setActive(bool active) { active_ = active; }

Circuit* CircuitView::circuit() { return circuit_; }
void CircuitView::setCircuit(Circuit* circuit)
{
    if (circuit != NULL) {
        disconnect(circuit, SIGNAL(updated()), this, SLOT(repaint()));
    }
    circuit_ = circuit; update();
    connect(circuit, SIGNAL(updated()), this, SLOT(repaint()));
}

Point CircuitView::mapFromCoordinate(Point point) { return mapFromCoordinate(point.x(), point.y()); }
Point CircuitView::mapFromCoordinate(long double x, long double y)
{
    Point coord;
    coord.setX((x - position().x()) * pixelsPerUnit() / width() + 0.5);
    coord.setY((y - position().y()) * pixelsPerUnit() / height() + 0.5);
    return coord;
}

Point CircuitView::mapToCoordinate(Point point) { return mapToCoordinate(point.x(), point.y()); }
Point CircuitView::mapToCoordinate(long double x, long double y)
{
    Point pos;
    pos.setX((x - 0.5)*width() / pixelsPerUnit() + position().x());
    pos.setY((y - 0.5)*height() / pixelsPerUnit() + position().y());
    return pos;
}

Point CircuitView::toScreen(QPoint point) { return toScreen(point.x(), point.y()); }
Point CircuitView::toScreen(QPointF point) { return toScreen(point.x(), point.y()); }
Point CircuitView::toScreen(Point point) { return toScreen(point.x(), point.y()); }
Point CircuitView::toScreen(long double x, long double y) {
    return Point(x/width(), y/height());
}

QPoint CircuitView::toPixels(Point point) { return toPixels(point.x(), point.y()); }
QPoint CircuitView::toPixels(long double x, long double y)
{
    return QPoint(x*width(), y*height());
}

long double CircuitView::dmod(long double x, long double y) { return x - floor(x/y)*y; }

void CircuitView::translate(long double x, long double y, bool update) { translate(Point(x, y), update); }
void CircuitView::translate(Point position, bool update) { position_ += position; if(update) this->update(); }

long double CircuitView::pixelsPerUnit() { return pixelsPerUnit_; }
void CircuitView::updatePixelsPerUnit() { pixelsPerUnit_ = qMax<long double>(width(), height()) / MIN_ZOOM * zoom() / MAX_ZOOM; }

Point CircuitView::position() { return position_; }
void CircuitView::setPosition(Point position) { setPosition(position.x(), position.y()); }
void CircuitView::setPosition(long double x, long double y)
{
    position_.setX(x);
    position_.setY(y);
    update();
}

Point CircuitView::positionVelocity() { return positionVelocity_; }
void CircuitView::setPositionVelocity(Point velocity) { setPositionVelocity(velocity.x(), velocity.y()); }
void CircuitView::setPositionVelocity(long double x, long double y)
{
    lastPositionVelocity_.setX(positionVelocity_.x());
    lastPositionVelocity_.setY(positionVelocity_.y());
    positionVelocity_.setX(x);
    positionVelocity_.setY(y);
}

long double CircuitView::zoom() { return zoom_; }
void CircuitView::setZoom(long double zoom, bool update) { setZoom(zoom, mapToCoordinate(Point(0.5, 0.5)), update); }
void CircuitView::setZoom(long double zoom, Point point, bool update)
{
    Point coord = mapToCoordinate(point);
    zoom_ = qMin<long double>(MAX_ZOOM, qMax<long double>(MIN_ZOOM, zoom));
    updatePixelsPerUnit();

    setPosition(coord - Point(width()*(point.x()-0.5)/pixelsPerUnit(), height()*(point.y()-0.5)/pixelsPerUnit()));

    if (update)
        repaint();

}
void CircuitView::setZoom(Point pointAi, Point pointBi, Point pointAf, Point pointBf, bool update)
{
    Point hotSpot = (pointAf + pointBf)/2;

    Vector a(width()*(pointAi.x() - pointBi.x()), height()*(pointAi.y() - pointBi.y()));
    Vector b(width()*(pointAf.x() - pointBf.x()), height()*(pointAf.y() - pointBf.y()));

    long double newZoom = zoom() * b.length() / a.length();
    setZoom(newZoom, hotSpot, update);
}
