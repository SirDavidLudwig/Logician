#ifndef CIRCUITVIEW_H
#define CIRCUITVIEW_H

#include <QBrush>
#include <QContextMenuEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QPointF>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QWidget>

class CircuitView : public QWidget
{
    Q_OBJECT
public:
    const int MIN_ZOOM = 10;
    const int MAX_ZOOM = 100;

    CircuitView(QWidget *parent = 0);

    QPointF mapToCoordinate(QPointF point);
    QPointF mapToCoordinate(double x, double y);

    QPoint toPixels(QPointF point);
    QPoint toPixels(double x, double y);

    double pixelsPerUnit();
    double zoom();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *event);

    void drawGrid(QPaintEvent *event, QPainter &painter);

private:
    QPointF mousePos_;
    double pixelsPerUnit_;

    double zoom_;

signals:

public slots:
    void updatePixelsPerUnit();
    void setZoom(double zoom);
};

#endif // CIRCUITVIEW_H
