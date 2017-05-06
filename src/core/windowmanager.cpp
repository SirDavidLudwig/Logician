#include "windowmanager.h"

WindowManager::WindowManager(QObject *parent) :
    QObject(parent)
{

}

MainWindow* WindowManager::newWindow()
{
    MainWindow *window = new MainWindow();
    connect(window, SIGNAL(closed(MainWindow*)), this, SLOT(removeWindow(MainWindow*)));
    windowList_.append(window);
    return window;
}

void WindowManager::removeWindow(MainWindow *window)
{
    disconnect(window, SIGNAL(closed(MainWindow*)), this, SLOT(removeWindow(MainWindow*)));
    windowList_.removeOne(window);
}

QList<MainWindow*> WindowManager::windows() { return windowList_; }
