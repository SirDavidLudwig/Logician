#ifndef MAINWINDOWTOOLBAR_H
#define MAINWINDOWTOOLBAR_H

#include <QToolBar>
#include <QWidget>

#include "../utils/iconloader.h"

class MainWindowToolBar : public QToolBar
{
    Q_OBJECT
public:
    MainWindowToolBar(QWidget *parent = 0);

signals:

public slots:
};

#endif // MAINWINDOWTOOLBAR_H
