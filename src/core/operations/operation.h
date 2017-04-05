#ifndef OPERATION_H
#define OPERATION_H

class Circuit;

class Operation
{
public:
    Operation();

    virtual void revert(Circuit *circuit) = 0;
    virtual void execute(Circuit *circuit) = 0;
};

#endif // OPERATION_H
