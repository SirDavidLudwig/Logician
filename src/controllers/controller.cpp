#include "controller.h"

Controller::Controller(Controller::Type type) :
    QObject(), type_(type)
{

}

Controller::Type Controller::type() { return type_; }
