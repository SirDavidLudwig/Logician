#ifndef CIRCUITVIEW_H
#define CIRCUITVIEW_H

#include <QBrush>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

class CircuitView : public QWidget
{
    Q_OBJECT
public:
    CircuitView(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // CIRCUITVIEW_H
