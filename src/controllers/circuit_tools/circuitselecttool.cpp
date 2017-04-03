#include "circuitselecttool.h"
#include "../../widgets/circuitview.h"

CircuitSelectTool::CircuitSelectTool() :
    CircuitTool(SelectTool)
{

}

bool CircuitSelectTool::mousePressEvent(CircuitView *view, QMouseEvent *event)
{
    CircuitComponent *component;

    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() & Qt::ShiftModifier) {
            component = view->componentAt(view->mapToCoordinate(view->toScreen(event->pos())));
            if (component != nullptr)
                view->circuit()->toggleSelectComponent(component);

        } else {
            view->circuit()->deselectAll(false); // Deselect all, but don't repaint just yet
            component = view->componentAt(view->mapToCoordinate(view->toScreen(event->pos())));
            if (component != nullptr)
                view->circuit()->selectComponent(component, false);
            view->repaint(); // Ok, now repaint
        }
    }
    return false;
}
