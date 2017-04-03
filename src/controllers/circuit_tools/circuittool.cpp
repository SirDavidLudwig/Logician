#include "circuittool.h"
#include "../../widgets/circuitview.h"

CircuitTool::CircuitTool(Tool tool) :
    tool_(tool)
{
}

bool CircuitTool::event(CircuitView *view, QEvent *event)
{
    return false;
}

bool CircuitTool::keyPressEvent(CircuitView *view, QKeyEvent *event)
{
    return false;
}

bool CircuitTool::keyReleaseEvent(CircuitView *view, QKeyEvent *event)
{
    return false;
}

bool CircuitTool::mouseMoveEvent(CircuitView *view, QMouseEvent *event)
{
    return false;
}

bool CircuitTool::mousePressEvent(CircuitView *view, QMouseEvent *event)
{
    return false;
}

bool CircuitTool::mouseReleaseEvent(CircuitView *view, QMouseEvent *event) // Execute before the last move event to get the velocity
{
    return false;
}

bool CircuitTool::wheelEvent(CircuitView *view, QWheelEvent *event)
{
    return false;
}

bool CircuitTool::touchEvent(CircuitView *view, QTouchEvent *event)
{
    return false;
}
