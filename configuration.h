#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QSettings>

class Configuration{     
public:
    Configuration();

    static QString language();
    static QString apiKey();

private:
    static QSettings *m_settings;
};

#endif // CONFIGURATION_H
