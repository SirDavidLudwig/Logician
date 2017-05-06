#include "actionmanager.h"

ActionManager::ActionManager(QObject *parent) :
    parent_(parent)
{
    createActions();
}

void ActionManager::createActions()
{
    addAction(About,            "action.about");
    addAction(CloseAllCircuits, "action.circuit_close_all");
    addAction(CloseCircuit,     "action.circuit_close",     QKeySequence(QKeySequence::Close));
    addAction(CloseWindow,      "action.window_close");
    addAction(Copy,             "action.copy",              QKeySequence(QKeySequence::Copy));
    addAction(Cut,              "action.cut",               QKeySequence(QKeySequence::Cut));
    addAction(Delete,           "action.delete",            QKeySequence(QKeySequence::Delete));
    addAction(Exit,             "action.exit",              QKeySequence(QKeySequence::Quit));
    addAction(Export,           "action.export");
    addAction(Import,           "action.import");
    addAction(NewProject,       "action.project_new",       QKeySequence(QKeySequence::New));
    addAction(NewWindow,        "action.window_new");
    addAction(OpenProject,      "action.project_open",      QKeySequence(QKeySequence::Open));
    addAction(Paste,            "action.paste",             QKeySequence(QKeySequence::Paste));
    addAction(Preferences,      "action.preferences");
    addAction(Redo,             "action.redo",              QKeySequence("Ctrl+Shift+Z"),      Disabled);
    addAction(Save,             "action.save",              QKeySequence(QKeySequence::Save));
    addAction(SaveAll,          "action.save_all");
    addAction(SaveAs,           "action.save_as",           QKeySequence("Ctrl+Shift+S"));
    addAction(ShowGrid,         "action.show_grid",         QKeySequence("Ctrl+G"),            Checkable|Checked);
    addAction(RevertCircuit,    "action.circuit_revert");
    addAction(Undo,             "action.undo",              QKeySequence(QKeySequence::Undo),  Disabled);
}

QAction* ActionManager::addAction(Action key, QString label, QKeySequence shortcut, int flags)
{
    QAction *action = new QAction(Locale::get(label), this);

    if (shortcut != 0)
        action->setShortcut(shortcut);

    if (flags != 0) {
        if (flags & Checkable)
            action->setCheckable(true);

        if (flags & Checked)
            action->setChecked(true);

        if (flags & Disabled)
            action->setEnabled(false);
    }

    actionMap_[key] = action;

    return action;
}

QAction* ActionManager::get(Action action) { return actionMap_[action]; }
