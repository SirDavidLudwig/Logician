#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QUrl>

#include "actionmanager.h"
#include "locale.h"
#include "windowmanager.h"
#include "../gui/mainwindow.h"


class Application : public QApplication
{
public:
    static Application* instance();

    Application(int argc, char *argv[]);

    ActionManager *actionManager();
    WindowManager* windowManager();


private:
    static Application* instance_;
    ActionManager *actionManager_;
    WindowManager *windowManager_;

public slots:
    void styleApp();
};

#endif // APPLICATION_H
