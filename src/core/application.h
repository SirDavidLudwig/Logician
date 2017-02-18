#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QFile>
#include <QIODevice>
#include <QObject>
#include <QUrl>

#include "../gui/mainwindow.h"


class Application : public QApplication
{
public:
    Application(int argc, char *argv[]);

    MainWindow* mainWindow();

private:
    MainWindow *mainWindow_;

public slots:
    void styleApp();
};

#endif // APPLICATION_H
