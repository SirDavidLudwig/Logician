#include "undoredostack.h"

Operation* UndoRedoStack::undo()
{
    if (undoStack_.isEmpty())
        return nullptr;

    Operation *operation = undoStack_.pop();
    redoStack_.push(operation);
    return operation;
}

Operation* UndoRedoStack::redo()
{
    if (redoStack_.isEmpty())
        return nullptr;

    Operation *operation = redoStack_.pop();
    undoStack_.push(operation);
    return operation;
}

void UndoRedoStack::push(Operation *operation)
{
    redoStack_.clear();
    undoStack_.push(operation);
}
