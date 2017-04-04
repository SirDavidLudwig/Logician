#include "circuitview.h"
#include "../gui/mainwindow.h"

CircuitView::CircuitView(QWidget *parent, Circuit *circuit) :
    QWidget(parent)
{
    active_ = false;
    circuit_ = NULL;
    touchDragging_ = false;
    pixelsPerUnit_ = 1;
    zoom_ = MAX_ZOOM / 6;

    setFocusPolicy(Qt::StrongFocus);
    setCircuit(circuit);
}

bool CircuitView::event(QEvent *event)
{
    // Forward touch events
    if (event->type() == QEvent::TouchBegin ||
        event->type() == QEvent::TouchUpdate ||
        event->type() == QEvent::TouchEnd ||
        event->type() == QEvent::TouchCancel)
    {
        touchEvent((QTouchEvent*) event);
    }

    // Disable key auto-repeat
    else if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease) {
        if (((QKeyEvent*)event)->isAutoRepeat())
            return true;
    }

    return this->QWidget::event(event);
}

void CircuitView::keyPressEvent(QKeyEvent *event)
{
    if (controller_ == nullptr)
        return;

    controller_->keyPressEvent(this, event);
}

void CircuitView::keyReleaseEvent(QKeyEvent *event)
{
    if (controller_ == nullptr)
        return;

    controller_->keyReleaseEvent(this, event);
}

void CircuitView::mouseMoveEvent(QMouseEvent *event)
{
    if (controller_ == nullptr)
        return;

    controller_->mouseMoveEvent(this, event);
}

void CircuitView::mousePressEvent(QMouseEvent *event)
{
    if (controller_ == nullptr)
        return;

    controller_->mousePressEvent(this, event);
}

void CircuitView::mouseReleaseEvent(QMouseEvent *event) // Execute before the last move event to get the velocity
{
    if (controller_ == nullptr)
        return;

    controller_->mouseReleaseEvent(this, event);
}

void CircuitView::wheelEvent(QWheelEvent *event)
{
    if (controller_ == nullptr)
        return;

    controller_->wheelEvent(this, event);
}

void CircuitView::touchEvent(QTouchEvent *event)
{
    if (controller_ == nullptr)
        return;

    controller_->touchEvent(this, event);
}

void CircuitView::resizeEvent(QResizeEvent *event)
{
    updatePixelsPerUnit();
}

void CircuitView::paintEvent(QPaintEvent *event)
{
    bool doRepaint = false;

    if (isPositionFalloffEnabled_) {
        if (sqrt(pow(positionVelocity().x(), 2) + pow(positionVelocity().y(), 2)) > 0.001) {
            translate(positionVelocity(), false);
            setPositionVelocity(positionVelocity() - positionVelocity() * MIN_ZOOM * 0.45 / zoom());
            doRepaint = true;
        }
    } else {
        translate(positionVelocity(), false);
        setPositionVelocity(0, 0);
    }

    QPainter painter;

    painter.begin(this);

    QFont font("Tahoma", 15);
    painter.setFont(font);

    if (controller_ != nullptr)
        controller_->preDraw(this, painter);

    drawGrid(event, painter);
    drawComponents(event, painter);

    if (controller_ != nullptr)
        controller_->draw(this, painter);

    painter.end();

    if (doRepaint)
        update();
}

void CircuitView::drawGrid(QPaintEvent *event, QPainter &painter)
{
    QPen pen = painter.pen();
    pen.setColor(QColor("#404040"));
    pen.setWidth(1);
    painter.setPen(pen);

    double x = Math::dmod(double(width()/2.0) - pixelsPerUnit()*position().x(), pixelsPerUnit());
    double y = Math::dmod(double(height()/2.0) - pixelsPerUnit()*position().y(), pixelsPerUnit());
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
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

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

CircuitViewController* CircuitView::controller() { return controller_; }
void CircuitView::setController(CircuitViewController *controller)
{
    controller_ = controller;
}

CircuitComponent* CircuitView::componentAt(QPointF point) { return componentAt(point.x(), point.y()); }
CircuitComponent* CircuitView::componentAt(double x, double y)
{
    foreach (CircuitComponent* component, circuit_->components()) {
        if (component->boundingBox().contains(x, y))
            return component;
    }
    return nullptr;
}

QPointF CircuitView::mapFromCoordinate(QPointF point) { return mapFromCoordinate(point.x(), point.y()); }
QPointF CircuitView::mapFromCoordinate(double x, double y)
{
    QPointF coord;
    coord.setX((x - position().x()) * pixelsPerUnit() / width() + 0.5);
    coord.setY((y - position().y()) * pixelsPerUnit() / height() + 0.5);
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

bool CircuitView::isPositionFalloffEnabled() { return isPositionFalloffEnabled_; }
void CircuitView::setPositionFalloffEnabled(bool enabled) { isPositionFalloffEnabled_ = enabled; }

void CircuitView::translate(double x, double y, bool update) { translate(QVector2D(x, y), update); }
void CircuitView::translate(QVector2D position, bool update) { position_ += position.toPointF(); if(update) this->update(); }

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

QVector2D CircuitView::positionVelocity() { return positionVelocity_; }
QVector2D CircuitView::lastPositionVelocity() { return lastPositionVelocity_; }
void CircuitView::setPositionVelocity(QVector2D velocity) { setPositionVelocity(velocity.x(), velocity.y()); }
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

    QVector2D a(width()*(pointAi.x() - pointBi.x()), height()*(pointAi.y() - pointBi.y()));
    QVector2D b(width()*(pointAf.x() - pointBf.x()), height()*(pointAf.y() - pointBf.y()));

    double newZoom = zoom() * b.length() / a.length();
    setZoom(newZoom, hotSpot, update);
}
