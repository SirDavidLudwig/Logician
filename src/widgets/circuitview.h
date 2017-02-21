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
#include <QWheelEvent>
#include <QWidget>

class CircuitView : public QWidget
{
    Q_OBJECT
public:
    const int MIN_ZOOM = 10;
    const int MAX_ZOOM = 100;

    CircuitView(QWidget *parent = 0);

    QPointF map(QPoint position);
    QPointF map(QPointF position);
    QPointF map(int x, int y);

    QPointF position();
    int zoom();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *event);

private:

    QPoint mousePos_;
    QPointF dragLastPoint_;
    QPointF position_;
    double goalZoom_;
    double zoom_;

signals:

public slots:
    void setPosition(QPoint point);
    void setPosition(QPointF point);
    void setZoom(int zoom);
};

#endif // CIRCUITVIEW_H
