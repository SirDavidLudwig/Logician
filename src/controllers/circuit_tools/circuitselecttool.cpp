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
    static QVector2D lastAnchorDelta(0, 0);
    anchorEnd_ = view->mapToCoordinate(view->toScreen(event->pos()));

    if (boxSelect_) {
        view->repaint();
    } else if (componentSelect_) {
        QVector2D anchorDelta(QPointF(round(anchorEnd_.x() - anchorStart_.x()), round(anchorEnd_.y() - anchorStart_.y())));
        if (anchorDelta != lastAnchorDelta) {
            view->setUpdatesEnabled(false);
            foreach(CircuitComponent *component, view->circuit()->selectedComponents()) {
                component->setPosition(component->markedPosition() + anchorDelta.toPointF());
            }
            view->setUpdatesEnabled(true);
        }
        lastAnchorDelta = anchorDelta;
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
            if (component != nullptr) {
                view->circuit()->toggleSelectComponent(component);
                if (component->isSelected()) {
                    componentSelect_ = true;
                    foreach (CircuitComponent *component, view->circuit()->selectedComponents())
                        component->markPosition();
                }
            }

        } else {
            if (component != nullptr) {
                if (!component->isSelected())
                    view->circuit()->deselectAll(false); // Deselect all, but don't repaint just yet
                view->circuit()->selectComponent(component, false);
                componentSelect_ = true;
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

        componentSelect_ = false;

        if (boxSelect_) {
            boxSelect_ = false;

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

            view->repaint();
        }
        boxSelect_ = false;
        multiSelect_ = false;
    }
    return false;
}
