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
#include "../utils/point.h"
#include "../utils/vector.h"

class CircuitView : public QWidget
{
    Q_OBJECT
public:
    const int MIN_ZOOM = 10;
    const int MAX_ZOOM = 100;

    CircuitView(QWidget *parent, Circuit *circuit = NULL);

    Circuit* circuit();

    long double dmod(long double x, long double y); // A fix for fmod

    bool isActive();

    Point mapFromCoordinate(Point point);
    Point mapFromCoordinate(long double x, long double y);

    Point mapToCoordinate(Point point);
    Point mapToCoordinate(long double x, long double y);

    QPoint toPixels(Point point);
    QPoint toPixels(long double x, long double y);

    Point toScreen(QPoint point);
    Point toScreen(QPointF point);
    Point toScreen(Point point);
    Point toScreen(long double x, long double y);

    Point position();
    Point positionVelocity();

    long double pixelsPerUnit();
    long double zoom();

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

    Vector lastPositionVelocity_;
    Vector positionVelocity_;
    Point position_;
    Point mousePos_;
    long double pixelsPerUnit_;

    long double zoom_;

public slots:
    void setActive(bool active);

    void setCircuit(Circuit* circuit);

    void translate(Point position, bool update = true);
    void translate(long double x, long double y, bool update = true);

    void setPosition(Point position);
    void setPosition(long double x, long double y);

    void setPositionVelocity(Point velocity);
    void setPositionVelocity(long double x, long double y);

    void setZoom(long double zoom, bool update = true);
    void setZoom(long double zoom, Point point, bool update = true);
    void setZoom(Point pointAi, Point pointBi, Point pointAf, Point pointBf, bool update = true);

protected slots:
    void updatePixelsPerUnit();
};

#endif // CIRCUITVIEW_H
