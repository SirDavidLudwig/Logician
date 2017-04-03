#include "circuitselecttool.h"
#include "../../widgets/circuitview.h"

CircuitSelectTool::CircuitSelectTool() :
    CircuitTool(SelectTool)
{

}

bool CircuitSelectTool::draw(CircuitView *view, QPainter &painter)
{
    if (boxSelect_) {
        painter.setRenderHint(QPainter::Antialiasing, false);

        QPen pen(Qt::red);
        pen.setColor(QColor(155, 155, 155, 220));
        pen.setWidth(1);
        painter.setPen(pen);

        QRectF rect = QRectF(
            view->toPixels(view->mapFromCoordinate(anchorStart_)),
            view->toPixels(view->mapFromCoordinate(anchorEnd_))
        ).normalized();

        painter.fillRect(rect, QColor(100, 100, 100, 128));
        painter.drawRect(rect);
    }
    return false;
}

bool CircuitSelectTool::mouseMoveEvent(CircuitView *view, QMouseEvent *event)
{
    if (boxSelect_) {
        anchorEnd_ = view->mapToCoordinate(view->toScreen(event->pos()));
        view->repaint();
    }
    return false;
}

bool CircuitSelectTool::mousePressEvent(CircuitView *view, QMouseEvent *event)
{
    CircuitComponent *component;


    if (event->button() == Qt::LeftButton) {

        anchorStart_ = view->mapToCoordinate(view->toScreen(event->pos()));
        anchorEnd_ = anchorStart_;

        component = view->componentAt(anchorStart_);

        if (component == nullptr) {
            boxSelect_ = true;
        }

        if (event->modifiers() & Qt::ShiftModifier) {
            multiSelect_ = true;
            if (component != nullptr)
                view->circuit()->toggleSelectComponent(component);

        } else {
            view->circuit()->deselectAll(false); // Deselect all, but don't repaint just yet
            if (component != nullptr)
                view->circuit()->selectComponent(component, false);
            view->repaint(); // Ok, now repaint
        }
    }
    return false;
}

bool CircuitSelectTool::mouseReleaseEvent(CircuitView *view, QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (boxSelect_) {
            boxSelect_ = false;

            QRectF rect = QRectF(anchorStart_, anchorEnd_).normalized();

            if (multiSelect_)
                foreach (CircuitComponent *component, view->circuit()->components()) {
                    if (rect.contains(component->boundingBox()))
                        view->circuit()->toggleSelectComponent(component, false);
                }

            else
                foreach (CircuitComponent *component, view->circuit()->components()) {
                    if (rect.contains(component->boundingBox()))
                        view->circuit()->selectComponent(component, false);
                }

            view->repaint();
        }
        boxSelect_ = false;
        multiSelect_ = false;
    }
    return false;
}
