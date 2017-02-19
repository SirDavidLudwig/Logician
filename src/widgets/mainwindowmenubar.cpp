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
}

void MainWindowMenuBar::addAction(QString menu, QAction *action)
{
    menu_.value(menu)->addAction(action);
}

void MainWindowMenuBar::addMenu(QString label)
{
    QMenu* menu = this->QMenuBar::addMenu(label);
    menu_.insert(menu->title(), menu);
}

void MainWindowMenuBar::addSeparator(QString menu)
{
    menu_.value(menu)->addSeparator();
}
