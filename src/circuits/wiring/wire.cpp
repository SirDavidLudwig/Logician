#include "wire.h"

Wire::Wire() :
    QObject()
{

}

void Wire::onUpdate()
{
    foreach(CircuitSocket *socket, sources_) {

    }
}

void Wire::addSocket(CircuitSocket *socket)
{
    if (socket->type() == CircuitSocket::Sink && !sinks_.contains(socket)) {
        sinks_.append(socket);
    } else if (socket->type() == CircuitSocket::Source && !sources_.contains(socket)) {
        sources_.append(socket);
        connect(socket, SIGNAL(update()), this, SLOT(onUpdate()));
    }
}

void Wire::removeSocket(CircuitSocket *socket)
{
    if (socket->type() == CircuitSocket::Sink && sinks_.contains(socket)) {
        sinks_.removeOne(socket);
    } else if (socket->type() == CircuitSocket::Source && sources_.contains(socket)) {
        sources_.removeOne(socket);
        disconnect(socket, SIGNAL(update()), this, SLOT(onUpdate()));
    }
}
