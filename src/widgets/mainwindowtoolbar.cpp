#include "mainwindowtoolbar.h"

MainWindowToolBar::MainWindowToolBar(QWidget *parent) :
    QToolBar(parent)
{
    setMovable(false);
    QSize iconSize(20, 20);
    setIconSize(iconSize);
    addAction(IconLoader::load("mouse-pointer", iconSize), "Select");
    addAction(IconLoader::load("resistor", iconSize), "Wiring");
    addAction(IconLoader::load("hand-paper-o", iconSize), "Pan");
    addAction(IconLoader::load("search-plus", iconSize), "Zoom In");
    addAction(IconLoader::load("search-minus", iconSize), "Zoom Out");
}
