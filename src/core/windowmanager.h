#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QList>
#include <QObject>

#include "../gui/mainwindow.h"

class WindowManager : public QObject
{
    Q_OBJECT
public:
    WindowManager(QObject *parent = 0);

    QList<MainWindow*> windows();

private:
    QList<MainWindow*> windowList_;

signals:

public slots:
    MainWindow* newWindow();
    void removeWindow(MainWindow *window);
};

#endif // WINDOWMANAGER_H
