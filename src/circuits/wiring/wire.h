#ifndef WIRE_H
#define WIRE_H

#include <QObject>

#include "../circuitsocket.h"

class Wire : public QObject
{
    Q_OBJECT
public:
    Wire();

private:

    QList<CircuitSocket*> sources_;
    QList<CircuitSocket*> sinks_;

signals:

public slots:
    void addSocket(CircuitSocket *socket);
    void removeSocket(CircuitSocket *socket);

    void onUpdate();
};

#endif // WIRE_H
