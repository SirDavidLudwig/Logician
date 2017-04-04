#ifndef MAINWINDOWUI_H
#define MAINWINDOWUI_H

#include <QTabWidget>
#include <QWidget>

#include "circuitview.h"
#include "../controllers/controllermanager.h"

class MainWindow;

class MainWindowUi : public QTabWidget
{
    Q_OBJECT
public:
    MainWindowUi(QWidget *parent = 0);

private:
    MainWindow *mainWindow_;
    int lastTab_;

signals:

public slots:
    void addCircuit(Circuit *circuit);

    void onTabChange(int index);
    void tabInserted(int index);
};

#endif // MAINWINDOWUI_H
