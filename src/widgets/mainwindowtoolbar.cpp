#include "mainwindowtoolbar.h"

MainWindowToolBar::MainWindowToolBar(QWidget *parent) :
    QToolBar(parent)
{
    setMovable(false);
    QSize iconSize(20, 20);
    setIconSize(iconSize);
    addAction(IconLoader::load("mouse-QPointFer", iconSize), "Select Mode");
    addAction(IconLoader::load("hand-paper-o", iconSize), "Select Mode");
    addAction(IconLoader::load("search-plus", iconSize), "Select Mode");
    addAction(IconLoader::load("search-minus", iconSize), "Select Mode");
}
