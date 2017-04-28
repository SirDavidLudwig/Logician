#ifndef MAINWINDOWMENUBAR_H
#define MAINWINDOWMENUBAR_H

#include <QMap>
#include <QMenuBar>
#include <QWidget>

#include "../core/locale.h"

class MainWindowMenuBar : public QMenuBar
{
    Q_OBJECT
public:

    MainWindowMenuBar(QWidget *parent);

    void addAction(QString menu, QAction *action, QKeySequence shortcut = 0);
    void addMenu(QString label);
    void addSeparator(QString menu);

protected:
    void style();

    void addFileActions();
    void addEditActions();
    void addViewActions();
    void addToolsActions();
    void addWindowActions();
    void addHelpActions();

private:
    QMap<QString, QMenu*> menus_;

signals:

public slots:
};

#endif // MAINWINDOWMENUBAR_H
