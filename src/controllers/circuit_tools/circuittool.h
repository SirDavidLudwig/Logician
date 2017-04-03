#ifndef CIRCUITTOOL_H
#define CIRCUITTOOL_H

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QWheelEvent>

class CircuitView;

class CircuitTool
{
public:
    enum Tool {
        AddComponentTool,
        PanTool,
        SelectTool,
        WiringTool
    };

    CircuitTool(Tool tool);

    virtual bool preDraw(CircuitView *view, QPainter &painter);
    virtual bool draw(CircuitView *view, QPainter &painter);

    virtual bool event(CircuitView *view, QEvent *event);
    virtual bool keyPressEvent(CircuitView *view, QKeyEvent *event);
    virtual bool keyReleaseEvent(CircuitView *view, QKeyEvent *event);
    virtual bool mouseMoveEvent(CircuitView *view, QMouseEvent *event);
    virtual bool mousePressEvent(CircuitView *view, QMouseEvent *event);
    virtual bool mouseReleaseEvent(CircuitView *view, QMouseEvent *event);
    virtual bool wheelEvent(CircuitView *view, QWheelEvent *event);
    virtual bool touchEvent(CircuitView* view, QTouchEvent *event);

private:
    Tool tool_;

};

#endif // CIRCUITTOOL_H
