#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QMap>
#include <QObject>

#include "controller.h"

class ControllerManager
{
public:
    static Controller* controller(QObject *key);

    static void addController(QObject *key, Controller *controller);
    static void removeController(QObject *key);

    static QMap<QObject*, Controller*> *controllers_;

private:

};

#endif // CONTROLLERMANAGER_H
