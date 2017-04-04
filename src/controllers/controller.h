#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
public:

    enum Type {
        CircuitViewController
    };

    Controller(Type type);

    Type type();

private:
    const Controller::Type type_;

signals:

public slots:
};

#endif // CONTROLLER_H
