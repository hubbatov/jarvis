#include <QDir>

#include "configuration.h"

QString pathToConfig = QString("%1/.jarvis/config.ini").arg(QDir::homePath());

QSettings* Configuration::m_settings = new QSettings(pathToConfig, QSettings::IniFormat);

Configuration::Configuration(){
}

QString Configuration::language(){
    return m_settings->value("api/language").toString();
}

QString Configuration::apiKey(){
    return m_settings->value("api/key").toString();
}
