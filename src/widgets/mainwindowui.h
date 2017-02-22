#ifndef MAINWINDOWUI_H
#define MAINWINDOWUI_H

#include <QTabWidget>
#include <QWidget>

#include "circuitview.h"

class MainWindowUi : public QTabWidget
{
    Q_OBJECT
public:
    MainWindowUi(QWidget *parent = 0);

private:
    int lastTab_;

signals:

public slots:
    void onTabChange(int index);
    void tabInserted(int index);
};

#endif // MAINWINDOWUI_H
