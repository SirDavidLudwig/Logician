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

signals:

public slots:
};

#endif // MAINWINDOWUI_H
