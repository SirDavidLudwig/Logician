#include "locale.h"

QLocale::Language language_ = QLocale::English;
QMap<QString, QString> langMap_;

QString Locale::get(QString id)
{
    if (langMap_.contains(id))
        return langMap_[id];
    qWarning() << "Locale ID not found:" << id;
    return id;
}

QLocale::Language Locale::language() { return language_; }
void Locale::setLanguage(QLocale::Language language)
{
    QStringList parts;

    language_ = language;
    QFile file(":/lang/" + QLocale::languageToString(language_) + ".lang");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    while (!file.atEnd()) {
        parts = QString(file.readLine()).split('=');
        if (parts.length() > 1)
            langMap_.insert(parts[0].trimmed(), parts[1].trimmed());
    }

    file.close();
}
