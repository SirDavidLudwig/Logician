#ifndef CIRCUITVIEW_H
#define CIRCUITVIEW_H

#include <iostream>
#include <stdio.h>

#include <QBrush>
#include <QContextMenuEvent>
#include <QDebug>
#include <QEvent>
#include <QGL>
#include <QGLFormat>
#include <QGLWidget>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPanGesture>
#include <QPoint>
#include <QPointF>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QWidget>

#include "../circuits/circuit.h"
#include "../circuits/circuitcomponent.h"

class CircuitView : public QWidget
{
    Q_OBJECT
public:
    const int MIN_ZOOM = 10;
    const int MAX_ZOOM = 100;

    CircuitView(QWidget *parent, Circuit *circuit = NULL);

    Circuit* circuit();

    double dmod(double x, double y); // A fix for fmod
    double magnitude(QPoint point);
    double magnitude(QPointF point);

    bool isActive();

    QPointF mapFromCoordinate(QPointF point);
    QPointF mapFromCoordinate(double x, double y);

    QPointF mapToCoordinate(QPointF point);
    QPointF mapToCoordinate(double x, double y);

    QPoint toPixels(QPointF point);
    QPoint toPixels(double x, double y);

    QPointF toScreen(QPoint point);
    QPointF toScreen(QPointF point);
    QPointF toScreen(double x, double y);

    QPointF position();
    QPointF positionVelocity();

    double pixelsPerUnit();
    double zoom();

protected:
    bool event(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawGrid(QPaintEvent *event, QPainter &painter);
    void drawComponents(QPaintEvent *event, QPainter &painter);

private:
    Circuit *circuit_;

    bool active_;
    bool touchDragging_;
    bool dragging_;

    QPointF lastPositionVelocity_;
    QPointF positionVelocity_;
    QPointF position_;
    QPointF mousePos_;
    double pixelsPerUnit_;

    double zoom_;

public slots:
    void setActive(bool active);

    void setCircuit(Circuit* circuit);

    void translate(QPointF position, bool update = true);
    void translate(double x, double y, bool update = true);

    void setPosition(QPointF position);
    void setPosition(double x, double y);

    void setPositionVelocity(QPointF velocity);
    void setPositionVelocity(double x, double y);

    void setZoom(double zoom, bool update = true);
    void setZoom(double zoom, QPointF point, bool update = true);
    void setZoom(QPointF pointAi, QPointF pointBi, QPointF pointAf, QPointF pointBf, bool update = true);

protected slots:
    void updatePixelsPerUnit();
};

#endif // CIRCUITVIEW_H
