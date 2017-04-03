#ifndef CIRCUITVIEWCONTROLLER_H
#define CIRCUITVIEWCONTROLLER_H

#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QObject>
#include <QTouchEvent>
#include <QWheelEvent>

#include "circuit_tools/circuittool.h"
#include "circuit_tools/circuitaddcomponenttool.h"
#include "circuit_tools/circuitpantool.h"
#include "circuit_tools/circuitselecttool.h"
#include "circuit_tools/circuitwiringtool.h"

class CircuitView;

class CircuitViewController : public QObject
{
    Q_OBJECT
public:
    CircuitViewController();

    void preDraw(CircuitView *view, QPainter &painter);
    void draw(CircuitView *view, QPainter &painter);

    bool event(CircuitView *view, QEvent *event);
    void keyPressEvent(CircuitView *view, QKeyEvent *event);
    void keyReleaseEvent(CircuitView *view, QKeyEvent *event);
    void mouseMoveEvent(CircuitView *view, QMouseEvent *event);
    void mousePressEvent(CircuitView *view, QMouseEvent *event);
    void mouseReleaseEvent(CircuitView *view, QMouseEvent *event);
    void wheelEvent(CircuitView *view, QWheelEvent *event);
    void touchEvent(CircuitView* view, QTouchEvent *event);

    CircuitTool* activeTool();

private:
    CircuitTool *activeTool_ = nullptr;

    QList<CircuitTool*> backgroundTools_;

signals:

public slots:
    void setActiveTool(CircuitTool *tool);
    void setActiveTool(CircuitTool::Tool tool);
};

#endif // CIRCUITVIEWCONTROLLER_H
