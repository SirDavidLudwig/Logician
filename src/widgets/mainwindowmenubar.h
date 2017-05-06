#ifndef MAINWINDOWMENUBAR_H
#define MAINWINDOWMENUBAR_H

#include <QMap>
#include <QMenuBar>
#include <QWidget>

#include "../core/actionmanager.h"
#include "../core/locale.h"

class MainWindowMenuBar : public QMenuBar
{
    Q_OBJECT
public:

    MainWindowMenuBar(QWidget *parent);

protected:
    void style();

    void addFileActions();
    void addEditActions();
    void addViewActions();
    void addToolsActions();
    void addWindowActions();
    void addHelpActions();

private:
    ActionManager *actionManager_;

signals:

public slots:
};

#endif // MAINWINDOWMENUBAR_H
