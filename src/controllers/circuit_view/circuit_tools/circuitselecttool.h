#ifndef CIRCUITSELECTTOOL_H
#define CIRCUITSELECTTOOL_H

#include "circuittool.h"

#include "../../../core/operations/circuit/movecomponentoperation.h"

class CircuitSelectTool: public CircuitTool
{
public:
    CircuitSelectTool();

    bool draw(CircuitView *view, QPainter &painter);

    bool keyPressEvent(CircuitView *view, QKeyEvent *event);
    bool mouseMoveEvent(CircuitView *view, QMouseEvent *event);
    bool mousePressEvent(CircuitView *view, QMouseEvent *event);
    bool mouseReleaseEvent(CircuitView *view, QMouseEvent *event);

protected:
    QVector2D anchorDelta();
    QVector2D anchorDeltaRounded();

    void boxSelectStartEvent(CircuitView *view, QMouseEvent *event);
    void boxSelectEndEvent(CircuitView *view, QMouseEvent *event);

    void componentMoveDragEvent(CircuitView *view, QMouseEvent *event);
    void componentMoveEndEvent(CircuitView *view, QMouseEvent *event);

    void componentPressEvent(CircuitView *view, CircuitComponent *component, QMouseEvent *event);


private:
    QPointF anchorStart_;
    QPointF anchorEnd_;

    bool boxSelecting_ = false;      // True when drag selecting
    bool multiSelect_ = false;    // True if Shift is held when selecting
    bool componentPressed_ = false; // True if left-mouse button press was on a component
    bool altDrag_ = false;

};

#endif // CIRCUITSELECTTOOL_H
