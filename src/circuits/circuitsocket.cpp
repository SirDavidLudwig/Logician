#include "circuitsocket.h"

CircuitSocket::CircuitSocket(SocketType type) :
    QObject(), type_(type), signal_(1)
{
}

CircuitSocket::SocketType CircuitSocket::type() const { return type_; }

QPoint CircuitSocket::position() { return position_; }
void CircuitSocket::setPosition(QPoint position) { position_ = position; }

CircuitSignal &CircuitSocket::signal() { return signal_; }
void CircuitSocket::setSignal(CircuitSignal &signal)
{
    signal_ = signal;
}

CircuitSocket::~CircuitSocket()
{

}
