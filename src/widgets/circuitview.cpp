#include "circuitview.h"

CircuitView::CircuitView(QWidget *parent) :
    QWidget(parent)
{
    setMouseTracking(true);

    pixelsPerUnit_ = 1;
    zoom_ = MIN_ZOOM;
}

void CircuitView::mouseMoveEvent(QMouseEvent *event)
{
    mousePos_ = QPointF(float(event->pos().x()) / width(), float(event->pos().y()) / height());
}

void CircuitView::mousePressEvent(QMouseEvent *event)
{

}

void CircuitView::mouseReleaseEvent(QMouseEvent *event)
{

}

void CircuitView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QFont font("Tahoma", 15);
    painter.setFont(font);

    drawGrid(event, painter);

    QPen pen = painter.pen();
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);

    painter.drawPoint(width()/2, 10);

    pen = painter.pen();
    pen.setColor(Qt::white);
    pen.setWidth(10);
    painter.setPen(pen);

    int line = 1;
    QPointF coord = mapToCoordinate(mousePos_);
    painter.drawText(QPoint(5, 20*line++), "Pixels per unit: " + QString::number(pixelsPerUnit()));
    painter.drawText(QPoint(5, 20*line++), "Mouse Pos(" + QString::number(mousePos_.x()) + ", " + QString::number(mousePos_.y()) + ")");
    painter.drawText(QPoint(5, 20*line++), "Coordinate(" + QString::number(coord.x()) + ", " + QString::number(coord.y()) + ")");
    painter.drawText(QPoint(5, 20*line++), "Zoom: " + QString::number(zoom()));
}

void CircuitView::resizeEvent(QResizeEvent *event)
{
    updatePixelsPerUnit();
}

void CircuitView::wheelEvent(QWheelEvent *event)
{
    setZoom(zoom() - zoom() * event->delta() / -1200);
    this->QWidget::wheelEvent(event);
}

void CircuitView::drawGrid(QPaintEvent *event, QPainter &painter)
{
    QPen pen = painter.pen();
    pen.setColor(QColor("#404040"));
    pen.setWidth(1);
    painter.setPen(pen);

    double x = fmod(width()/2, pixelsPerUnit());
    double y = fmod(height()/2, pixelsPerUnit());

    for (x; x < width(); x += pixelsPerUnit()) {
        painter.drawLine(round(x), 0, round(x), height());
    }

    for (y; y < height(); y += pixelsPerUnit()) {
        painter.drawLine(0, round(y), width(), round(y));
    }
}

QPointF CircuitView::mapToCoordinate(QPointF point) { return mapToCoordinate(point.x(), point.y()); }
QPointF CircuitView::mapToCoordinate(double x, double y)
{
    QPoint pixelPos = toPixels(x - 0.5, y - 0.5);
    QPointF pos;
    pos.setX(float(pixelPos.x()) / pixelsPerUnit());
    pos.setY(float(pixelPos.y()) / pixelsPerUnit());
    return pos;
}

QPoint CircuitView::toPixels(QPointF point) { return toPixels(point.x(), point.y()); }
QPoint CircuitView::toPixels(double x, double y)
{
    return QPoint(x*width(), y*height());
}

double CircuitView::pixelsPerUnit() { return pixelsPerUnit_; }

double CircuitView::zoom() { return zoom_; }
void CircuitView::setZoom(double zoom) { zoom_ = qMin<double>(MAX_ZOOM, qMax<double>(MIN_ZOOM, zoom)); updatePixelsPerUnit(); update(); }

void CircuitView::updatePixelsPerUnit() { pixelsPerUnit_ = qMax<float>(width(), height()) / MIN_ZOOM * zoom() / MAX_ZOOM; }

