#include "circuitselecttool.h"
#include "../../../widgets/circuitview.h"

CircuitSelectTool::CircuitSelectTool() :
    CircuitTool(SelectTool)
{

}

bool CircuitSelectTool::draw(CircuitView *view, QPainter &painter)
{
    if (boxSelecting_) {
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

void CircuitSelectTool::boxSelectStartEvent(CircuitView *view, QMouseEvent *event) {}
void CircuitSelectTool::boxSelectEndEvent(CircuitView *view, QMouseEvent *event)
{
    QRectF rect = QRectF(anchorStart_, anchorEnd_).normalized();

    if (multiSelect_)
        foreach (CircuitComponent *component, view->circuit()->components()) {
            if (rect.intersects(component->boundingBox()))
                view->circuit()->toggleSelectComponent(component, false);
        }

    else
        foreach (CircuitComponent *component, view->circuit()->components()) {
            if (rect.intersects(component->boundingBox()))
                view->circuit()->selectComponent(component, false);
        }

    boxSelecting_ = false; // Don't draw the box select thing on repaint
    view->repaint();
}

void CircuitSelectTool::componentMoveDragEvent(CircuitView *view, QMouseEvent *event)
{
    static QVector2D lastAnchorDelta(0, 0);

    QVector2D anchorDelta = anchorDeltaRounded();
    if (anchorDelta != lastAnchorDelta) {
        view->setUpdatesEnabled(false);

        foreach(CircuitComponent *component, view->circuit()->selectedComponents()) {
            component->setPosition(component->markedPosition() + anchorDelta.toPointF());
        }
        view->setUpdatesEnabled(true);
    }
    lastAnchorDelta = anchorDelta;
}

void CircuitSelectTool::componentMoveEndEvent(CircuitView *view, QMouseEvent *event)
{
    foreach (CircuitComponent *component, view->circuit()->selectedComponents()) {
        component->setPosition(component->markedPosition(), false);
    }

    view->circuit()->executeOperation(new MoveComponentOperation(view->circuit()->selectedComponents(), anchorDeltaRounded()));
}

void CircuitSelectTool::componentPressEvent(CircuitView *view, CircuitComponent *component, QMouseEvent *event)
{

}

bool CircuitSelectTool::keyPressEvent(CircuitView *view, QKeyEvent *event)
{
    CircuitComponent::Orientation orientation;

    switch(event->key()) {
        case Qt::Key_Up:
            orientation = CircuitComponent::North;
            break;
        case Qt::Key_Down:
            orientation = CircuitComponent::South;
            break;
        case Qt::Key_Left:
            orientation = CircuitComponent::West;
            break;
        case Qt::Key_Right:
            orientation = CircuitComponent::East;
            break;
        default:
            return false;
    }

    view->setUpdatesEnabled(false);
    foreach (CircuitComponent *component, view->circuit()->selectedComponents())
        component->setOrientation(orientation);
    view->setUpdatesEnabled(true);

    return true;
}

bool CircuitSelectTool::mouseMoveEvent(CircuitView *view, QMouseEvent *event)
{
    // Update the anchor
    anchorEnd_ = view->mapToCoordinate(view->toScreen(event->pos()));

    // Send events to appropriate methods
    if (boxSelecting_) {
        view->repaint();
    } else if (componentPressed_) {
        componentMoveDragEvent(view, event);
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
            boxSelecting_ = true;
        }

        if (event->modifiers() & Qt::ShiftModifier) {
            multiSelect_ = true;

            if (component != nullptr) {
                view->circuit()->toggleSelectComponent(component);
                if (component->isSelected()) {
                    componentPressed_ = true;

                    if (event->modifiers() & Qt::AltModifier)
                        altDrag_ = true;

                    foreach (CircuitComponent *component, view->circuit()->selectedComponents())
                        component->markPosition();
                }
            }

        } else {
            if (component != nullptr) {
                if (!component->isSelected())
                    view->circuit()->deselectAll(false); // Deselect all, but don't repaint just yet
                view->circuit()->selectComponent(component, false);
                componentPressed_ = true;

                if (event->modifiers() & Qt::AltModifier)
                    altDrag_ = true;

                foreach (CircuitComponent *component, view->circuit()->selectedComponents())
                    component->markPosition();
            } else {
                view->circuit()->deselectAll(false); // Deselect all, but don't repaint just yet
            }
            view->repaint(); // Ok, now repaint
        }
    }
    return false;
}

bool CircuitSelectTool::mouseReleaseEvent(CircuitView *view, QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        if (componentPressed_)
            componentMoveEndEvent(view, event);

        else if (boxSelecting_)
            boxSelectEndEvent(view, event);

        // Reset everything
        componentPressed_ = false;
        boxSelecting_ = false;
        multiSelect_ = false;
    }
    return false;
}

QVector2D CircuitSelectTool::anchorDelta()
{
    return QVector2D(anchorEnd_.x() - anchorStart_.x(), anchorEnd_.y() - anchorStart_.y());
}

QVector2D CircuitSelectTool::anchorDeltaRounded()
{
    return QVector2D(round(anchorEnd_.x() - anchorStart_.x()), round(anchorEnd_.y() - anchorStart_.y()));
}
