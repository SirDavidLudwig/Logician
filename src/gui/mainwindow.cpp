#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    menuBar_ = new MainWindowMenuBar();
    setMenuBar(menuBar_);

    ui_ = new MainWindowUi();
    setCentralWidget(ui_);
}
