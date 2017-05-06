#include "application.h"

// Store the application instance
Application* Application::instance_ = nullptr;
Application* Application::instance() { return Application::instance_; }

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    // Save an instance of the app
    Application::instance_ = this;

    // Set the app's language
    Locale::setLanguage(QLocale::English);

    // Create the action manager
    actionManager_ = new ActionManager(this);

    // Create the window manager
    windowManager_ = new WindowManager(this);

    // Make the app pretty
    styleApp();

    // Make and show the main window
    windowManager_->newWindow()->showMaximized();
}

void Application::styleApp()
{
    QFile styles(":/stylesheets/dark.css");
    styles.open(QIODevice::ReadOnly | QIODevice::Text);

    setStyleSheet(QString(styles.readAll()));

    styles.close();
}

ActionManager* Application::actionManager() { return actionManager_; }
WindowManager* Application::windowManager() { return windowManager_; }
