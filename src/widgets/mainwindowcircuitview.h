#ifndef MAINWINDOWUI_H
#define MAINWINDOWUI_H

#include <QTabWidget>
#include <QWidget>

#include "circuitview.h"

class MainWindow;

class MainWindowCircuitView : public QTabWidget
{
    Q_OBJECT
public:
    MainWindowCircuitView(QWidget *parent = 0);

    void setController(CircuitViewController *controller);

private:
    MainWindow *mainWindow_;
    int lastTab_;

    CircuitViewController *controller_;

signals:

public slots:
    void addCircuit(Circuit *circuit);

    void onTabChange(int index);
    void tabInserted(int index);
};

#endif // MAINWINDOWUI_H
