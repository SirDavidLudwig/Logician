#include "mainwindowmenubar.h"

MainWindowMenuBar::MainWindowMenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    addMenu("File");
    addMenu("Edit");
    addMenu("View");
    addMenu("Tools");
    addMenu("Window");
    addMenu("Help");

    addFileActions();
    addEditActions();
    addViewActions();
    addToolsActions();
    addWindowActions();
    addHelpActions();
}

void MainWindowMenuBar::addAction(QString menu, QAction *action, QKeySequence shortcut)
{
    if (shortcut != 0)
        action->setShortcut(shortcut);
    menus_.value(menu)->addAction(action);
}

void MainWindowMenuBar::addMenu(QString label)
{
    QMenu* menu = QMenuBar::addMenu(label);
    menus_.insert(menu->title(), menu);
}

void MainWindowMenuBar::addSeparator(QString menu)
{
    menus_.value(menu)->addSeparator();
}

void MainWindowMenuBar::addFileActions()
{
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.new_project"), parent()), QKeySequence(QKeySequence::New));
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.open_project"), parent()), QKeySequence(QKeySequence::Open));
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.save"), parent()), QKeySequence(QKeySequence::Save));
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.save_as"), parent()), QKeySequence("Ctrl+Shift+S"));
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.save_all"), parent()));
    addSeparator("File");
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.close_circuit"), parent()), QKeySequence(QKeySequence::Close));
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.revert_circuit"), parent()));
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.close_all_circuits"), parent()));
    addSeparator("File");
    addAction("File", new QAction(Locale::get("mainwindow.menu.file.exit"), parent()), QKeySequence(QKeySequence::Quit));

}

void MainWindowMenuBar::addEditActions()
{
    addAction("Edit", new QAction(Locale::get("mainwindow.menu.edit.undo"), parent()), QKeySequence(QKeySequence::Undo));
    addAction("Edit", new QAction(Locale::get("mainwindow.menu.edit.redo"), parent()), QKeySequence("Ctrl+Shift+Z"));
    addSeparator("Edit");
    addAction("Edit", new QAction(Locale::get("mainwindow.menu.edit.copy"), parent()), QKeySequence(QKeySequence::Save));
    addAction("Edit", new QAction(Locale::get("mainwindow.menu.edit.cut"), parent()), QKeySequence("Ctrl+Shift+S"));
    addAction("Edit", new QAction(Locale::get("mainwindow.menu.edit.paste"), parent()));
    addSeparator("Edit");
    addAction("Edit", new QAction(Locale::get("mainwindow.menu.edit.delete"), parent()), QKeySequence(QKeySequence::Close));
}

void MainWindowMenuBar::addViewActions()
{
    addAction("View", new QAction(Locale::get("mainwindow.menu.view.show_grid"), parent()));
}

void MainWindowMenuBar::addToolsActions()
{

}

void MainWindowMenuBar::addWindowActions()
{

}

void MainWindowMenuBar::addHelpActions()
{
    addAction("Help", new QAction("About", parent()));
}
