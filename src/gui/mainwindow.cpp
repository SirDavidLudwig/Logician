#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    browser_ = new AssetBrowser(this);
    addDockWidget(Qt::RightDockWidgetArea, browser_);

    toolBar_ = new MainWindowToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolBar_);

    menuBar_ = new MainWindowMenuBar(this);
    setMenuBar(menuBar_);

    ui_ = new MainWindowUi(this);
    setCentralWidget(ui_);
}
