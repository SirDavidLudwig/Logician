#include "circuitpantool.h"
#include "../../../widgets/circuitview.h"

CircuitPanTool::CircuitPanTool(Qt::MouseButton button) :
    CircuitTool(PanTool)
{
    panButton_ = button;
}

bool CircuitPanTool::mouseMoveEvent(CircuitView *view, QMouseEvent *event)
{
    QPointF newPos = view->toScreen(event->pos());
    if (event->buttons() & panButton_) {
        view->setPositionVelocity(QVector2D(view->mapToCoordinate(mousePos_) - view->mapToCoordinate(newPos)));
        mousePos_ = newPos;
        view->update();
        return true;
    }
    return false;
}

bool CircuitPanTool::mousePressEvent(CircuitView *view, QMouseEvent *event)
{
    bool result = false;

    if (event->button() == panButton_) {
        dragging_ = true;
        view->setCursor(Qt::ClosedHandCursor);
        view->setPositionFalloffEnabled(!(dragging_ || touchDragging_));
        view->setPositionVelocity(0, 0);
        result = true;
    }

    mousePos_.setX(double(event->pos().x()) / view->width());
    mousePos_.setY(double(event->pos().y()) / view->height());

    return result;
}

bool CircuitPanTool::mouseReleaseEvent(CircuitView *view, QMouseEvent *event) // Execute before the last move event to get the velocity
{
    if (event->button() == panButton_) {
        dragging_ = false;
        view->setCursor(Qt::ArrowCursor);
        view->setPositionFalloffEnabled(!(dragging_ || touchDragging_));

        mousePos_.setX(double(event->pos().x()) / view->width());
        mousePos_.setY(double(event->pos().y()) / view->height());

        return true;
    }

    return false;
}

bool CircuitPanTool::wheelEvent(CircuitView *view, QWheelEvent *event)
{
    if (event->angleDelta().y() == 0)
        return false;

    int direction = event->angleDelta().y() / -abs(event->angleDelta().y());
    view->setZoom(view->zoom() - view->zoom() * 0.1 * direction, view->toScreen(event->pos()));
    return true;
}

bool CircuitPanTool::touchEvent(CircuitView *view, QTouchEvent *event)
{
    if (event->touchPoints().length() == 2) {

        touchDragging_ = true;
        view->setPositionFalloffEnabled(!(dragging_ || touchDragging_));

        QTouchEvent::TouchPoint pointA = event->touchPoints()[0];
        QTouchEvent::TouchPoint pointB = event->touchPoints()[1];

        QPointF lastHotSpot = view->toScreen(pointA.lastPos() + pointB.lastPos()) / 2;
        QPointF newHotSpot = view->toScreen(pointA.pos() + pointB.pos()) / 2;
        mousePos_ = lastHotSpot;

        QPointF lastA = view->toScreen(pointA.lastPos());
        QPointF lastB = view->toScreen(pointB.lastPos());

        QPointF newA = view->toScreen(pointA.pos());
        QPointF newB = view->toScreen(pointB.pos());

        if (pointA.state() != Qt::TouchPointReleased && pointB.state() != Qt::TouchPointReleased) {
            view->setZoom(lastA, lastB, newA, newB, false);
            view->setPositionVelocity(QVector2D(view->mapToCoordinate(mousePos_) - view->mapToCoordinate(newHotSpot)));
            mousePos_ = newHotSpot;
            view->repaint();
        } else {
            view->setPositionFalloffEnabled(!(dragging_ || touchDragging_));
            view->setPositionVelocity(view->lastPositionVelocity());
            mousePos_.setX(newHotSpot.x());
            mousePos_.setY(newHotSpot.y());
            view->repaint();
        }

        return true;

    } else {
        touchDragging_ = false;
        view->setPositionFalloffEnabled(!(dragging_ || touchDragging_));
        return true;
    }

    return false;
}
