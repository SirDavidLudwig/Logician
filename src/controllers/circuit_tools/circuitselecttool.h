#ifndef CIRCUITSELECTTOOL_H
#define CIRCUITSELECTTOOL_H

#include "circuittool.h"

class CircuitSelectTool: public CircuitTool
{
public:
    CircuitSelectTool();

    bool draw(CircuitView *view, QPainter &painter);

    bool keyPressEvent(CircuitView *view, QKeyEvent *event);
    bool mouseMoveEvent(CircuitView *view, QMouseEvent *event);
    bool mousePressEvent(CircuitView *view, QMouseEvent *event);
    bool mouseReleaseEvent(CircuitView *view, QMouseEvent *event);

private:
    QPointF anchorStart_;
    QPointF anchorEnd_;

    bool boxSelect_ = false;
    bool multiSelect_ = false;
    bool componentSelect_ = false;
    bool altDrag_ = false;

};

#endif // CIRCUITSELECTTOOL_H
