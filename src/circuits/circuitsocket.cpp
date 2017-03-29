#include "circuitsocket.h"

CircuitSocket::CircuitSocket(SocketType type) :
    QObject(), type_(type)
{

}

const CircuitSocket::SocketType CircuitSocket::type() { return type_; }
