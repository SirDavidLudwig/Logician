#include "mainwindowmenubar.h"

MainWindowMenuBar::MainWindowMenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    addMenu("File");
    addMenu("Help");
}
