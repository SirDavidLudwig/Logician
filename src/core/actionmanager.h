#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QAction>
#include <QKeySequence>
#include <QObject>
#include <QString>

#include "locale.h"

class ActionManager: public QObject
{
    Q_OBJECT
public:
    enum Action {
        About,
        CloseAllCircuits,
        CloseCircuit,
        CloseWindow,
        Copy,
        Cut,
        Delete,
        Exit,
        Export,
        Import,
        NewProject,
        NewWindow,
        OpenProject,
        Paste,
        Preferences,
        Redo,
        RevertCircuit,
        Save,
        SaveAll,
        SaveAs,
        ShowGrid,
        Undo

    };

    enum Flags {
        Checked = 0x1,
        Checkable = 0x2,
        Disabled = 0x4,
    };

    ActionManager(QObject *parent = 0);

    QAction* get(Action action);

protected:
    void createActions();
    QAction* addAction(Action key, QString label, QKeySequence shortcut = 0, int flags = 0);

private:
    const QObject *parent_;
    QMap<ActionManager::Action, QAction*> actionMap_;
};

#endif // ACTIONMANAGER_H
