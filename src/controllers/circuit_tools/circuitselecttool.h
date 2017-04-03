#ifndef CIRCUITSELECTTOOL_H
#define CIRCUITSELECTTOOL_H

#include "circuittool.h"

class CircuitSelectTool: public CircuitTool
{
public:
    CircuitSelectTool();

    bool draw(CircuitView *view, QPainter &painter);

    bool mouseMoveEvent(CircuitView *view, QMouseEvent *event);
    bool mousePressEvent(CircuitView *view, QMouseEvent *event);
    bool mouseReleaseEvent(CircuitView *view, QMouseEvent *event);

private:
    QPointF anchorStart_;
    QPointF anchorEnd_;

    bool boxSelect_;
    bool multiSelect_;
};

#endif // CIRCUITSELECTTOOL_H
