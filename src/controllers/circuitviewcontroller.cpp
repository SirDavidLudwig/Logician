#include "circuitviewcontroller.h"
#include "../widgets/circuitview.h"

CircuitViewController::CircuitViewController() :
    QObject()
{
    // Background tools
    backgroundTools_.append(new CircuitPanTool(Qt::MiddleButton));

    setActiveTool(new CircuitSelectTool());
}

void CircuitViewController::preDraw(CircuitView *view, QPainter &painter)
{
    if (!activeTool_->preDraw(view, painter))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->preDraw(view, painter);
}

void CircuitViewController::draw(CircuitView *view, QPainter &painter)
{
    if (!activeTool_->draw(view, painter))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->draw(view, painter);
}

bool CircuitViewController::event(CircuitView *view, QEvent *event)
{
    return activeTool_->event(view, event);
}

void CircuitViewController::keyPressEvent(CircuitView *view, QKeyEvent *event)
{
    if (!activeTool_->keyPressEvent(view, event))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->keyPressEvent(view, event);

    if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_X) {
        deleteSelected(view);
    }
}

void CircuitViewController::keyReleaseEvent(CircuitView *view, QKeyEvent *event)
{
    if (!activeTool_->keyReleaseEvent(view, event))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->keyReleaseEvent(view, event);
}

void CircuitViewController::mouseMoveEvent(CircuitView *view, QMouseEvent *event)
{
    if (!activeTool_->mouseMoveEvent(view, event))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->mouseMoveEvent(view, event);
}

void CircuitViewController::mousePressEvent(CircuitView *view, QMouseEvent *event)
{
    if (!activeTool_->mousePressEvent(view, event))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->mousePressEvent(view, event);
}

void CircuitViewController::mouseReleaseEvent(CircuitView *view, QMouseEvent *event)
{
    if (!activeTool_->mouseReleaseEvent(view, event))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->mouseReleaseEvent(view, event);
}

void CircuitViewController::wheelEvent(CircuitView *view, QWheelEvent *event)
{
    if (!activeTool_->wheelEvent(view, event))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->wheelEvent(view, event);
}

void CircuitViewController::touchEvent(CircuitView *view, QTouchEvent *event)
{
    if (!activeTool_->touchEvent(view, event))
        foreach(CircuitTool *tool, backgroundTools_)
            tool->touchEvent(view, event);
}

CircuitTool* CircuitViewController::activeTool() { return activeTool_; }
void CircuitViewController::setActiveTool(CircuitTool *tool)
{
    if (activeTool_ != nullptr)
        delete activeTool_;
    activeTool_ = tool;
}

void CircuitViewController::deleteSelected(CircuitView *view)
{
    view->setUpdatesEnabled(false);
    view->circuit()->deleteSelected();
    view->setUpdatesEnabled(true);
}
