#ifndef MAINWINDOWMENUBAR_H
#define MAINWINDOWMENUBAR_H

#include <QMenuBar>
#include <QWidget>

class MainWindowMenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MainWindowMenuBar(QWidget *parent = 0);

protected:
    void style();

private:

signals:

public slots:
};

#endif // MAINWINDOWMENUBAR_H
