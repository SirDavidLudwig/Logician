#include "application.h"
#include "../utils/point.h"
#include "../utils/vector.h"

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    styleApp();

    mainWindow_ = new MainWindow();
    mainWindow_->showMaximized();
}

void Application::styleApp()
{
    QFile styles(":/stylesheets/dark.css");
    styles.open(QIODevice::ReadOnly | QIODevice::Text);

    setStyleSheet(QString(styles.readAll()));

    styles.close();

}

MainWindow* Application::mainWindow() { return mainWindow_; }
