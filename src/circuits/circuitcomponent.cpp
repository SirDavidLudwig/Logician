#include "circuitcomponent.h"
#include "circuit.h"

const QColor CircuitComponent::COLOR_DEFAULT = QColor("#9b9b9b");
const QColor CircuitComponent::COLOR_SELECTED = QColor("#e64c3c");

CircuitComponent::CircuitComponent(QPointF position, CircuitComponent::Orientation orientation) :
    QObject()
{
    setBoundingBox(QRectF(0, 0, 0, 0));
    selected_ = false;
    position_ = position;
    orientation_ = orientation;
}

void CircuitComponent::addInput(QPoint position)
{
    CircuitSocket *socket = new CircuitSocket(CircuitSocket::Source);
    socket->setPosition(position);
    inputs_.append(socket);
    connect(socket, SIGNAL(updated(CircuitSocket*)), this, SLOT(inputUpdate(CircuitSocket*)));
}

void CircuitComponent::addOutput(QPoint position)
{
    CircuitSocket *socket = new CircuitSocket(CircuitSocket::Source);
    socket->setPosition(position);
    outputs_.append(socket);
}

void CircuitComponent::removeInput(int index)
{
    CircuitSocket *socket = inputs_.takeAt(index);

    if (socket) {
        disconnect(socket, SIGNAL(updated(CircuitSocket*)), this, SLOT(inputUpdate(CircuitSocket*)));
        socket->deleteLater();
    }
}

void CircuitComponent::removeOutput(int index)
{
    CircuitSocket *socket = outputs_.takeAt(index);

    if (socket) {
        socket->deleteLater();
    }
}

void CircuitComponent::clearInputs()
{
    for (int i = inputs_.length(); i > 0; i++)
        removeInput(0);
}

void CircuitComponent::clearOutputs()
{
    for (int i = outputs_.length(); i > 0; i++)
        removeOutput(0);
}

Circuit* CircuitComponent::circuit() { return circuit_; }
void CircuitComponent::setCircuit(Circuit *circuit)
{
    circuit_ = circuit;
}

bool CircuitComponent::isSelected() { return selected_; }
void CircuitComponent::setSelected(bool selected) { selected_ = selected; }

CircuitComponent::Orientation CircuitComponent::orientation() { return orientation_; }
void CircuitComponent::setOrientation(Orientation orientation) { orientation_ = orientation; update(); }

QRectF CircuitComponent::boundingBox() { return boundingBox_; }
void CircuitComponent::setBoundingBox(QRectF bounds)
{
    QRectF tBounds;
    if (orientation_ == East)
        tBounds = bounds;
    else if (orientation_ == West) {
        tBounds.setTopLeft(-bounds.bottomRight());
        tBounds.setBottomRight(-bounds.topLeft());
    }
    else if (orientation_ == North) {
        tBounds.setTopRight(QPointF(bounds.bottomRight().y(), -bounds.bottomRight().x()));
        tBounds.setBottomLeft(QPointF(bounds.topLeft().y(), -bounds.topLeft().x()));
    }
    else {
        tBounds.setTopRight(QPointF(-bounds.topLeft().y(), bounds.topLeft().x()));
        tBounds.setBottomLeft(QPointF(-bounds.bottomRight().y(), bounds.bottomRight().x()));
    }

    tBounds.setTopLeft(position_ + tBounds.topLeft());
    tBounds.setBottomRight(position_ + tBounds.bottomRight());

    boundingBox_ = tBounds;
}

QPointF CircuitComponent::markedPosition() { return markedPosition_; }
void CircuitComponent::markPosition() { markedPosition_ = position_; }

QPointF CircuitComponent::position() { return position_; }
void CircuitComponent::setPosition(QPointF position) { position_ = position; update(); }

void CircuitComponent::update() { emit updated(); }

void CircuitComponent::prepareDraw(QPainter &painter, QPointF position, QSize screen, double pixelsPerUnit)
{
    viewportPosition_ = position;
    screen_ = screen;
    pixelsPerUnit_ = pixelsPerUnit;

    QTransform transform = painter.transform();

    transform.translate((screen.width()/2) + (position_.x() - viewportPosition_.x())*pixelsPerUnit_ + 1,
                        (screen.height()/2) + (position_.y() - viewportPosition_.y())*pixelsPerUnit_ + 1);

    switch(orientation_) {
        case North:
            transform.rotate(-90);
            break;
        case South:
            transform.rotate(90);
            break;
        case West:
            transform.rotate(180);
            break;
    }

    painter.setTransform(transform);
}

void CircuitComponent::draw(QPainter &painter)
{
    painter.setPen(pen());

    foreach (CircuitSocket *socket, inputs_) {
        painter.drawPoint(pointF(socket->position()));
    }

    foreach (CircuitSocket *socket, outputs_) {
        painter.drawPoint(pointF(socket->position()));
    }
}

void CircuitComponent::inputUpdate(CircuitSocket *socket) { Q_UNUSED(socket); }

QRectF CircuitComponent::rectF(double x, double y, double width, double height)
{
    return QRectF(pointF(x, y), QSizeF(width*pixelsPerUnit_, height*pixelsPerUnit_));
}

QPointF CircuitComponent::pointF(QPointF point) { return pointF(point.x(), point.y()); }
QPointF CircuitComponent::pointF(double x, double y)
{
    return QPointF(x * pixelsPerUnit_, y * pixelsPerUnit_);
}

QPen CircuitComponent::pen()
{
    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(isSelected() ? COLOR_SELECTED : COLOR_DEFAULT);
    pen.setWidth(2);
    return pen;
}
