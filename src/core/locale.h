#ifndef LOCALE_H
#define LOCALE_H

#include <QDebug>
#include <QLocale>
#include <QFile>
#include <QIODevice>
#include <QMap>
#include <QString>
#include <QStringList>

class Locale
{
public:
    static QString get(QString id);

    static QLocale::Language language();
    static void setLanguage(QLocale::Language language);

private:
    Locale();
};

#endif // LOCALE_H
