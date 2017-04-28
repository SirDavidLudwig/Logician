#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QUrl>

#include "locale.h"
#include "../gui/mainwindow.h"


class Application : public QApplication
{
public:
    static Application* instance();

    Application(int argc, char *argv[]);

    MainWindow* mainWindow();

private:
    static Application* instance_;
    MainWindow *mainWindow_;

public slots:
    void styleApp();
};

#endif // APPLICATION_H
