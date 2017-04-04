#include "controllermanager.h"

QMap<QObject*, Controller*> *ControllerManager::controllers_ = new QMap<QObject*, Controller*>();


Controller* ControllerManager::controller(QObject *key)
{
//    if (ControllerManager::controllers_.contains(key)) {
//        return ControllerManager::controllers_[key];
//    }
    ControllerManager::controllers_->count();
    return nullptr;
}

void ControllerManager::addController(QObject *key, Controller *controller)
{
//    ControllerManager::controllers_[key] = controller;
}

void ControllerManager::removeController(QObject *key)
{
//    if (ControllerManager::controllers_.contains(key)) {
//        ControllerManager::controllers_[key]->deleteLater();
//        ControllerManager::controllers_.remove(key);
//    }
}
