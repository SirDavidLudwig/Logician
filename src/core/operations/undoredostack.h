#ifndef UNDOREDOSTACK_H
#define UNDOREDOSTACK_H

#include <QStack>

#include "operation.h"

class UndoRedoStack
{
public:
    Operation* undo();
    Operation* redo();

    void push(Operation *operation);

private:
    QStack<Operation*> undoStack_;
    QStack<Operation*> redoStack_;
};

#endif // UNDOREDOSTACK_H
