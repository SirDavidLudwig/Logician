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
#include <QKeyEvent>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QPointF>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QWidget>

#include "../circuits/circuit.h"
#include "../circuits/circuitcomponent.h"
#include "../controllers/circuitviewcontroller.h"
#include "../utils/math.h"


class CircuitView : public QWidget
{
    Q_OBJECT
public:
    const int MIN_ZOOM = 10;
    const int MAX_ZOOM = 200;

    CircuitView(QWidget *parent, Circuit *circuit = NULL);

    Circuit* circuit();
    CircuitViewController* controller();

    bool isActive();

    CircuitComponent* componentAt(QPointF point);
    CircuitComponent* componentAt(double x, double y);

    QPointF mapFromCoordinate(QPointF point);
    QPointF mapFromCoordinate(double x, double y);

    QPointF mapToCoordinate(QPointF point);
    QPointF mapToCoordinate(double x, double y);

    QPoint toPixels(QPointF point);
    QPoint toPixels(double x, double y);

    QPointF toScreen(QPoint point);
    QPointF toScreen(QPointF point);
    QPointF toScreen(double x, double y);

    bool isPositionFalloffEnabled();

    QPointF position();
    QVector2D positionVelocity();
    QVector2D lastPositionVelocity();

    double pixelsPerUnit();
    double zoom();

protected:
    bool event(QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void touchEvent(QTouchEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawGrid(QPaintEvent *event, QPainter &painter);
    void drawComponents(QPaintEvent *event, QPainter &painter);

private:
    Circuit *circuit_;
    CircuitViewController *controller_;

    bool active_;
    bool touchDragging_;
    bool isPositionFalloffEnabled_ = true;

    QVector2D lastPositionVelocity_;
    QVector2D positionVelocity_;
    QPointF position_;
    QPointF mousePos_;
    double pixelsPerUnit_;

    double zoom_;

public slots:
    void setActive(bool active);

    void setCircuit(Circuit* circuit);
    void setController(CircuitViewController *controller);

    void setPositionFalloffEnabled(bool enabled);

    void translate(QVector2D position, bool update = true);
    void translate(double x, double y, bool update = true);

    void setPosition(QPointF position);
    void setPosition(double x, double y);

    void setPositionVelocity(QVector2D velocity);
    void setPositionVelocity(double x, double y);

    void setZoom(double zoom, bool update = true);
    void setZoom(double zoom, QPointF point, bool update = true);
    void setZoom(QPointF pointAi, QPointF pointBi, QPointF pointAf, QPointF pointBf, bool update = true); // Zoom to based off a change in QPointFs on the screen

protected slots:
    void updatePixelsPerUnit();
};

#endif // CIRCUITVIEW_H
