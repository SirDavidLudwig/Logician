#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../widgets/mainwindowmenubar.h"
#include "../widgets/mainwindowui.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private:
    MainWindowMenuBar *menuBar_;
    MainWindowUi *ui_;

signals:

public slots:
};

#endif // MAINWINDOW_H
