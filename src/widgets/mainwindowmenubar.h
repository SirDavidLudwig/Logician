#ifndef MAINWINDOWMENUBAR_H
#define MAINWINDOWMENUBAR_H

#include <QMap>
#include <QMenuBar>
#include <QWidget>

class MainWindowMenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MainWindowMenuBar(QWidget *parent = 0);

    void addAction(QString menu, QAction *action);
    void addMenu(QString label);
    void addSeparator(QString menu);

protected:
    void style();

private:
    QMap<QString, QMenu*> menu_;

signals:

public slots:
};

#endif // MAINWINDOWMENUBAR_H
