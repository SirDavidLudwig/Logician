#ifndef CIRCUITSOCKET_H
#define CIRCUITSOCKET_H

#include <QObject>

class CircuitSocket : public QObject
{
    Q_OBJECT
public:
    enum SocketType {
        Sink,
        Source
    };

    CircuitSocket(SocketType type);

    SocketType type() const;

private:
    const SocketType type_;

signals:
    void update();

public slots:
};

#endif // CIRCUITSOCKET_H
