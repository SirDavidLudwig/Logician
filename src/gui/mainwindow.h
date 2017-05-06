#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QDockWidget>
#include <QMainWindow>

#include "../controllers/circuit_view/circuitviewcontroller.h"
#include "../widgets/assetbrowser.h"
#include "../widgets/mainwindowmenubar.h"
#include "../widgets/mainwindowtoolbar.h"
#include "../widgets/mainwindowcircuitview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

    void setCircuitViewController(CircuitViewController *controller);

protected:
    void closeEvent(QCloseEvent *event);

private:
    AssetBrowser *browser_;
    MainWindowMenuBar *menuBar_;
    MainWindowToolBar *toolBar_;
    MainWindowCircuitView *ui_;

signals:
    void closed(MainWindow*);

public slots:
};

#endif // MAINWINDOW_H
