#include "circuitview.h"

CircuitView::CircuitView(QWidget *parent) : QWidget(parent)
{
    goalZoom_ = 10;
    zoom_ = 10;

    setObjectName("CircuitView");
}

void CircuitView::contextMenuEvent(QContextMenuEvent *event)
{
    this->QWidget::contextMenuEvent(event);
}

void CircuitView::mouseMoveEvent(QMouseEvent *event)
{
    mousePos_ = event->pos();

    if (event->buttons() & Qt::MiddleButton)
    {
        QPointF pos(position().x(), position().y());
        pos += map(event->pos()) - dragLastPoint_;
        qDebug() << dragLastPoint_;
        setPosition(pos);
        dragLastPoint_ = map(event->pos());
    }

    this->QWidget::mouseMoveEvent(event);
}

void CircuitView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton)
        dragLastPoint_ = map(event->pos());

    this->QWidget::mousePressEvent(event);
}

void CircuitView::mouseReleaseEvent(QMouseEvent *event)
{
    this->QWidget::mouseReleaseEvent(event);
}

void CircuitView::wheelEvent(QWheelEvent *event)
{
    setZoom(goalZoom_ - goalZoom_ * event->delta() / -1200);
    this->QWidget::wheelEvent(event);
}

void CircuitView::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    zoom_ = goalZoom_;

    QPainter painter(this);

    painter.setPen(QColor("#404040"));

//    for (int x = (width()/2 % (int)zoom()); x < width(); x += zoom())
//        painter.drawLine(x, 0, x, height());

//    for (int y = (height()/2 % (int)zoom()); y < height(); y += zoom())
//        painter.drawLine(0, y, width(), y);

    painter.drawLine(width()/2 + position_.x() * zoom(), 0, width()/2 + position_.x() * zoom(), height());
    painter.drawLine(0, height()/2 + position_.y() * zoom(), width(), height()/2 + position_.y() * zoom());

    if (abs(goalZoom_ - zoom_) > 0.001)
        update();

    painter.setFont(QFont("Tahoma", 15));
    painter.setPen(QColor("#bdbdbd"));
    QPointF pos = map(mousePos_);
    painter.drawText(QPoint(5, 20), "(" + QString::number(pos.x()) + ", " + QString::number(pos.y()) + ")" +
                     QString::number(zoom()) + ", " +
                     "(" + QString::number(position().x()) + ", " + QString::number(position().y()) + ")");
}

QPointF CircuitView::map(QPointF position) { return map(position.x(), position.y()); }
QPointF CircuitView::map(QPoint position) { return map(position.x(), position.y()); }
QPointF CircuitView::map(int x, int y)
{
    QPointF pos;

    pos.setX((x - width()/2) / goalZoom_);
    pos.setY((y - height()/2) / goalZoom_);

    return pos;
}

QPointF CircuitView::position() { return position_; }
int CircuitView::zoom() { return zoom_; }

void CircuitView::setPosition(QPoint position) { setPosition(QPointF(position.x(), position.y())); }
void CircuitView::setPosition(QPointF position) { position_ = position; update(); }
void CircuitView::setZoom(int zoom) { goalZoom_ = qMax(MIN_ZOOM, qMin(zoom, MAX_ZOOM)); update(); }

