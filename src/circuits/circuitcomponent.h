#ifndef CIRCUITENTITY_H
#define CIRCUITENTITY_H

#include <QColor>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QRectF>
#include <QSize>

#include "circuitsocket.h"

class Circuit;

class CircuitComponent : public QObject
{
    Q_OBJECT
public:

    static const QColor COLOR_DEFAULT;
    static const QColor COLOR_SELECTED;

    enum Orientation {
        North,
        East,
        South,
        West
    };

    CircuitComponent(QPointF position = QPointF(0, 0), Orientation orientation = East);

    Circuit* circuit();

    QList<CircuitSocket*> inputs();
    QList<CircuitSocket*> outputs();

    bool isSelected();

    QRectF boundingBox();

    QPointF markedPosition();

    QPointF position();
    Orientation orientation();

    QRectF rectF(double x, double y, double width, double height);
    QPointF pointF(double x, double y);
    QPointF pointF(QPointF point);

    QPen pen();

protected:
    void setBoundingBox(QRectF bounds);

    void addInput(QPoint position);
    void addOutput(QPoint position);

    void removeInput(int index);
    void removeOutput(int index);

    void clearInputs();
    void clearOutputs();


private:
    friend class Circuit;

    Circuit *circuit_ = nullptr;

    QList<CircuitSocket*> inputs_;
    QList<CircuitSocket*> outputs_;

    bool selected_;
    QRectF boundingBox_;
    Orientation orientation_;
    QPointF markedPosition_;
    QPointF position_;

    double pixelsPerUnit_;
    QPointF viewportPosition_;
    QSize screen_;

    void setCircuit(Circuit *circuit);
    void setSelected(bool selected);

signals:
    void updated();

public slots:
    void markPosition();

    void setPosition(QPointF position, bool doUpdate = true);
    void setOrientation(Orientation orientation, bool doUpdate = true);

    void prepareDraw(QPainter &painter, QPointF position, QSize screen, double pixelsPerUnit);
    void update();

    virtual void draw(QPainter &painter);
    virtual void inputUpdate(CircuitSocket *socket);

};

#endif // CIRCUITENTITY_H
