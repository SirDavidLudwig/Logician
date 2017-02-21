#ifndef ASSETBROWSER_H
#define ASSETBROWSER_H

#include <QDockWidget>
#include <QTabBar>
#include <QTabWidget>
#include <QWidget>

class AssetBrowser : public QDockWidget
{
    Q_OBJECT
public:
    AssetBrowser(QWidget *parent = 0);

private:
    QTabWidget *browser_;

signals:

public slots:
};

#endif // ASSETBROWSER_H
