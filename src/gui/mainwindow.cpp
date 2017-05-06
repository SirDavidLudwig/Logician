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

    ui_ = new MainWindowCircuitView(this);
    ui_->setController(new CircuitViewController());
    setCentralWidget(ui_);

    ui_->addCircuit(new Circuit("My circuit"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit closed(this);
}

void MainWindow::setCircuitViewController(CircuitViewController *controller)
{
    ui_->setController(controller);
}
