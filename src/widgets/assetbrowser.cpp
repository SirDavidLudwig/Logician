#include "assetbrowser.h"

AssetBrowser::AssetBrowser(QWidget *parent) :
    QDockWidget(parent)
{
    setObjectName("AssetBrowser");
    setTitleBarWidget(new QWidget());

    browser_ = new QTabWidget();
    browser_->setIconSize(QSize(32, 32));
    setWidget(browser_);

    browser_->insertTab(0, new QWidget(), QIcon(":/png/gates_accent.png"), "");
}
