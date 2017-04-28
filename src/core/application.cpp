#include "application.h"

Application* Application::instance_ = nullptr;
Application* Application::instance() { return Application::instance_; }

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    // Save an instance of the app
    Application::instance_ = this;

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
