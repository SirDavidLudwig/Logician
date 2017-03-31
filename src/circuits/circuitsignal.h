#ifndef CIRCUITSIGNAL_H
#define CIRCUITSIGNAL_H

#include <QList>

class CircuitSignal
{
public:
    CircuitSignal(int dataWidth);

    int dataWidth();
    void setDataWidth(int dataWidth);

    char pin(int index);
    void setPin(int index, char value);

private:
    int dataWidth_;
    QList<char> data_;
};

#endif // CIRCUITSIGNAL_H
