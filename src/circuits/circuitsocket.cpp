#include "circuitsocket.h"

CircuitSocket::CircuitSocket(SocketType type) :
    QObject(), type_(type)
{

}

CircuitSocket::SocketType CircuitSocket::type() const { return type_; }
