#ifndef CIRCUITPANTOOL_H
#define CIRCUITPANTOOL_H

#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QTouchEvent>
#include <QVector2D>
#include <QWheelEvent>

#include "circuittool.h"

class CircuitPanTool : public CircuitTool
{
public:
    CircuitPanTool(Qt::MouseButton button = Qt::MiddleButton);

    bool mouseMoveEvent(CircuitView *view, QMouseEvent *event);
    bool mousePressEvent(CircuitView *view, QMouseEvent *event);
    bool mouseReleaseEvent(CircuitView *view, QMouseEvent *event);
    bool wheelEvent(CircuitView *view, QWheelEvent *event);
    bool touchEvent(CircuitView* view, QTouchEvent *event);

private:
    QPointF mousePos_;
    bool dragging_ = false;
    bool touchDragging_ = false;

    Qt::MouseButton panButton_;
};

#endif // CIRCUITPANTOOL_H
