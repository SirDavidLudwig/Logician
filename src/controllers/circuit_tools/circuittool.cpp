#include "circuittool.h"
#include "../../widgets/circuitview.h"

CircuitTool::CircuitTool(Tool tool) :
    tool_(tool)
{
}

bool CircuitTool::preDraw(CircuitView *view, QPainter &painter)
{
    Q_UNUSED(view)
    Q_UNUSED(painter)

    return false;
}

bool CircuitTool::draw(CircuitView *view, QPainter &painter)
{
    Q_UNUSED(view)
    Q_UNUSED(painter)

    return false;
}

bool CircuitTool::event(CircuitView *view, QEvent *event)
{
    Q_UNUSED(view)
    Q_UNUSED(event)

    return false;
}

bool CircuitTool::keyPressEvent(CircuitView *view, QKeyEvent *event)
{
    Q_UNUSED(view)
    Q_UNUSED(event)

    return false;
}

bool CircuitTool::keyReleaseEvent(CircuitView *view, QKeyEvent *event)
{
    Q_UNUSED(view)
    Q_UNUSED(event)

    return false;
}

bool CircuitTool::mouseMoveEvent(CircuitView *view, QMouseEvent *event)
{
    Q_UNUSED(view)
    Q_UNUSED(event)

    return false;
}

bool CircuitTool::mousePressEvent(CircuitView *view, QMouseEvent *event)
{
    Q_UNUSED(view)
    Q_UNUSED(event)

    return false;
}

bool CircuitTool::mouseReleaseEvent(CircuitView *view, QMouseEvent *event) // Execute before the last move event to get the velocity
{
    Q_UNUSED(view)
    Q_UNUSED(event)

    return false;
}

bool CircuitTool::wheelEvent(CircuitView *view, QWheelEvent *event)
{
    Q_UNUSED(view)
    Q_UNUSED(event)

    return false;
}

bool CircuitTool::touchEvent(CircuitView *view, QTouchEvent *event)
{
    Q_UNUSED(view)
    Q_UNUSED(event)

    return false;
}
