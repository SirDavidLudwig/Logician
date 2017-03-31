#ifndef CIRCUITENTITY_H
#define CIRCUITENTITY_H

#include <QColor>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QSize>

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

    CircuitComponent(QPointF position = QPointF(0, 0), Orientation orientation = North);

    bool isSelected();
    void setSelected(bool selected);

    QPointF position();
    Orientation orientation();

    QRectF rectF(double x, double y, double width, double height);
    QPointF pointF(double x, double y);

    QPen pen();

private:
    bool selected_;
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
    void prepareDraw(QPainter &painter, QPointF position, QSize screen, double pixelsPerUnit);
    void update();

};

#endif // CIRCUITENTITY_H
