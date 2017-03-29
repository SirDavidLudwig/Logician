#include "circuitsignal.h"

CircuitSignal::CircuitSignal(int dataWidth)
{
    setDataWidth(dataWidth);
}

int CircuitSignal::dataWidth() { return dataWidth_; }
void CircuitSignal::setDataWidth(int dataWidth)
{
    data_.clear();
    for (int i = 0; i < dataWidth; i++)
        data_.append(0);
}

char CircuitSignal::pin(int index) { return data_[index]; }
void CircuitSignal::setPin(int index, char data)
{
    data_[index] = data;
}
