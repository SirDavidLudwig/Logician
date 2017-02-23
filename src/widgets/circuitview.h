#ifndef CIRCUITVIEW_H
#define CIRCUITVIEW_H

#include <iostream>
#include <stdio.h>

#include <QBrush>
#include <QContextMenuEvent>
#include <QDebug>
#include <QEvent>
#include <QGesture>
#include <QGestureEvent>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPanGesture>
#include <QPoint>
#include <QPointF>
#include <QResizeEvent>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>

class CircuitView : public QWidget
{
    Q_OBJECT
public:
    const int MIN_ZOOM = 10;
    const int MAX_ZOOM = 100;
    const double CURSOR_TICK_FREQUENCY = 1000.0/15.0; // 30 FPS

    CircuitView(QWidget *parent = 0, int id = 0);

    double dmod(double x, double y);

    QPointF mapFromCoordinate(QPointF point);
    QPointF mapFromCoordinate(double x, double y);

    QPointF mapToCoordinate(QPointF point);
    QPointF mapToCoordinate(double x, double y);

    QPointF toScreen(QPoint point);
    QPointF toScreen(QPointF point);
    QPointF toScreen(double x, double y);

    QPoint toPixels(QPointF point);
    QPoint toPixels(double x, double y);

    double pixelsPerUnit();
    QPointF position();
    QPointF positionVelocity();
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
    void drag();

private:
    int id_;
    bool active_;
    bool touchDragging_;
    bool dragging_;
    QPointF lastPositionVelocity_;
    QPointF positionVelocity_;
    QPointF position_;
    QPointF mousePos_;
    double pixelsPerUnit_;
    double zoom_;

signals:

public slots:
    void translate(QPointF position, bool update = true);
    void translate(double x, double y, bool update = true);
    void setPosition(QPointF position);
    void setPosition(double x, double y);
    void setPositionVelocity(QPointF velocity);
    void setPositionVelocity(double x, double y);
    void updatePixelsPerUnit();
    void setZoom(double zoom);

    void setActive(bool active);
};

#endif // CIRCUITVIEW_H
