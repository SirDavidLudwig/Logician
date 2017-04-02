#include "circuitviewcontroller.h"
#include "../widgets/circuitview.h"

CircuitViewController::CircuitViewController() :
    QObject()
{

}

bool CircuitViewController::event(CircuitView *view, QEvent *event)
{
    return false;
}

void CircuitViewController::keyPressEvent(CircuitView *view, QKeyEvent *event)
{
    qDebug() << "Pressed" << view;
}

void CircuitViewController::keyReleaseEvent(CircuitView *view, QKeyEvent *event)
{
    qDebug() << "Released";
}

void CircuitViewController::mouseMoveEvent(CircuitView *view, QMouseEvent *event)
{
    QPointF newPos = view->toScreen(event->pos());
    if (event->buttons() & Qt::RightButton) {
        view->setPositionVelocity(QVector2D(view->mapToCoordinate(mousePos_) - view->mapToCoordinate(newPos)));
        mousePos_ = newPos;
        view->update();
    }
}

void CircuitViewController::mousePressEvent(CircuitView *view, QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        dragging_ = true;
        view->setPositionFalloffEnabled(!(dragging_ || touchDragging_));
        view->setPositionVelocity(0, 0);
    } else if (event->button() == Qt::LeftButton) {
        CircuitComponent *component = view->componentAt(view->mapToCoordinate(view->toScreen(event->pos())));
        view->circuit()->deselectAll(false);
        if (component != nullptr) {
            view->circuit()->selectComponent(component, true);
        } else {
            view->circuit()->update();
        }
    }

    mousePos_.setX(double(event->pos().x()) / view->width());
    mousePos_.setY(double(event->pos().y()) / view->height());
}

void CircuitViewController::mouseReleaseEvent(CircuitView *view, QMouseEvent *event) // Execute before the last move event to get the velocity
{
    if (event->button() == Qt::RightButton) {
        dragging_ = false;
        view->setPositionFalloffEnabled(!(dragging_ || touchDragging_));

        mousePos_.setX(double(event->pos().x()) / view->width());
        mousePos_.setY(double(event->pos().y()) / view->height());
    }
}

void CircuitViewController::wheelEvent(CircuitView *view, QWheelEvent *event)
{
    int direction = event->angleDelta().y() / -abs(event->angleDelta().y());
    view->setZoom(view->zoom() - view->zoom() * 0.1 * direction, view->toScreen(event->pos()));
}

void CircuitViewController::touchEvent(CircuitView *view, QTouchEvent *event)
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

        qDebug() << QVector2D(view->mapToCoordinate(lastA) - view->mapToCoordinate(lastB)).length();

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
   } else {
        touchDragging_ = false;
        view->setPositionFalloffEnabled(!(dragging_ || touchDragging_));
   }
}
