#include "iconloader.h"

QIcon IconLoader::load(QString name, QSize size, QColor color)
{
    return load(name, size.width(), size.height(), color);
}

QIcon IconLoader::load(QString name, int width, int height, QColor color)
{
    QSvgRenderer renderer(QString(":/svg/" + name + ".svg"));

    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(0x00000000);

    QPainter painter(&image);
    renderer.render(&painter);

    QColor pixel;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            pixel = image.pixelColor(x, y);
            pixel.setRed(color.red());
            pixel.setGreen(color.green());
            pixel.setBlue(color.blue());
            image.setPixelColor(x, y, pixel);
        }
    }


    return QIcon(QPixmap::fromImage(image));
}
