#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QColor>
#include <QDebug>
#include <QIcon>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QRgb>
#include <QSvgRenderer>

class IconLoader
{
public:
    static QIcon load(QString name, QSize size, QColor color = QColor(0xb6, 0xb6, 0xb6));
    static QIcon load(QString name, int width, int height, QColor color = QColor(0xb6, 0xb6, 0xb6));
};

#endif // ICONLOADER_H
