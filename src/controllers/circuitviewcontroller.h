#ifndef CIRCUITVIEWCONTROLLER_H
#define CIRCUITVIEWCONTROLLER_H

#include <QDebug>
#include <QMouseEvent>
#include <QObject>
#include <QTouchEvent>
#include <QWheelEvent>

class CircuitView;

class CircuitViewController : public QObject
{
    Q_OBJECT
public:
    CircuitViewController();

    bool event(CircuitView *view, QEvent *event);
    void mouseMoveEvent(CircuitView *view, QMouseEvent *event);
    void mousePressEvent(CircuitView *view, QMouseEvent *event);
    void mouseReleaseEvent(CircuitView *view, QMouseEvent *event);
    void wheelEvent(CircuitView *view, QWheelEvent *event);
    void touchEvent(CircuitView* view, QTouchEvent *event);

private:
    QPointF mousePos_;
    bool dragging_ = false;
    bool touchDragging_ = false;



signals:

public slots:
};

#endif // CIRCUITVIEWCONTROLLER_H
