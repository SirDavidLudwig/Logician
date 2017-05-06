#include "mainwindowmenubar.h"
#include "../core/application.h"

MainWindowMenuBar::MainWindowMenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    actionManager_ = Application::instance()->actionManager();

    addFileActions();
    addEditActions();
    addViewActions();
    addToolsActions();
    addWindowActions();
    addHelpActions();
}

void MainWindowMenuBar::addFileActions()
{
    QMenu *menu = addMenu(Locale::get("menu.file"));
    menu->addAction(actionManager_->get(ActionManager::NewProject));
    menu->addAction(actionManager_->get(ActionManager::OpenProject));
    menu->addAction(actionManager_->get(ActionManager::Save));
    menu->addAction(actionManager_->get(ActionManager::SaveAs));
    menu->addAction(actionManager_->get(ActionManager::SaveAll));

    menu->addSeparator();

    menu->addAction(actionManager_->get(ActionManager::CloseCircuit));
    menu->addAction(actionManager_->get(ActionManager::RevertCircuit));
    menu->addAction(actionManager_->get(ActionManager::CloseAllCircuits));

    menu->addSeparator();

    menu->addAction(actionManager_->get(ActionManager::Exit));
}

void MainWindowMenuBar::addEditActions()
{
    QMenu *menu = addMenu(Locale::get("menu.edit"));
    menu->addAction(actionManager_->get(ActionManager::Undo));
    menu->addAction(actionManager_->get(ActionManager::Redo));
}

void MainWindowMenuBar::addViewActions()
{
    QMenu *menu = addMenu(Locale::get("menu.view"));
}

void MainWindowMenuBar::addToolsActions()
{
    QMenu *menu = addMenu(Locale::get("menu.tools"));
}

void MainWindowMenuBar::addWindowActions()
{
    QMenu *menu = addMenu(Locale::get("menu.window"));
}

void MainWindowMenuBar::addHelpActions()
{
    QMenu *menu = addMenu(Locale::get("menu.help"));
    menu->addAction(actionManager_->get(ActionManager::About));
}
