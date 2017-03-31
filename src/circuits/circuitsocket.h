#ifndef CIRCUITSOCKET_H
#define CIRCUITSOCKET_H

#include <QObject>
#include <QPoint>

#include "circuitsignal.h"

class CircuitSocket : public QObject
{
    Q_OBJECT
public:
    enum SocketType {
        Sink,
        Source
    };

    CircuitSocket(SocketType type);
    ~CircuitSocket();

    SocketType type() const;
    QPoint position();

    CircuitSignal &signal();

private:
    const SocketType type_;
    QPoint position_;
    CircuitSignal signal_;

signals:
    void updated(CircuitSocket*);

public slots:
    void setPosition(QPoint position);
    void setSignal(CircuitSignal &signal);
};

#endif // CIRCUITSOCKET_H
