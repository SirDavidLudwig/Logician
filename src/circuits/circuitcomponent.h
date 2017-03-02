#ifndef CIRCUITENTITY_H
#define CIRCUITENTITY_H

#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QSize>

class CircuitComponent : public QObject
{
    Q_OBJECT
public:

    enum Orientation {
        North,
        East,
        South,
        West
    };

    CircuitComponent(QPointF position = QPointF(0, 0), Orientation orientation = North);

    QPointF position();
    Orientation orientation();

    QRectF rectF(double x, double y, double width, double height);
    QPointF pointF(double x, double y);

private:
    Orientation orientation_;
    QPointF position_;

    double pixelsPerUnit_;
    QPointF viewportPosition_;
    QSize screen_;

signals:
    void updated();

public slots:
    void setPosition(QPointF position);
    void setOrientation(Orientation orientation);

    virtual void draw(QPainter &painter);
    void prepareDraw(QPointF position, QSize screen, double pixelsPerUnit);
    void update();

};

#endif // CIRCUITENTITY_H
