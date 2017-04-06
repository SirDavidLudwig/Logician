#ifndef CIRCUITVIEWCONTROLLER_H
#define CIRCUITVIEWCONTROLLER_H

#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QObject>
#include <QTouchEvent>
#include <QWheelEvent>

#include "../controller.h"
#include "circuit_tools/circuittool.h"
#include "circuit_tools/circuitaddcomponenttool.h"
#include "circuit_tools/circuitpantool.h"
#include "circuit_tools/circuitselecttool.h"
#include "circuit_tools/circuitwiringtool.h"

#include "../../core/operations/circuit/componentorientoperation.h"
#include "../../core/operations/circuit/removecomponentoperation.h"

class CircuitView;

class CircuitViewController : public Controller
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

    void deleteSelected(CircuitView *view);
    void orientSelected(CircuitView *view, CircuitComponent::Orientation orientation);
};

#endif // CIRCUITVIEWCONTROLLER_H
