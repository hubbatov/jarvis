#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QSettings>

class Configuration{
public:
	Configuration();

	static void checkConfig();

	static QString language();
	static QString apiKey();
	static int attentionSeconds();

	static void fetchConfiguration();
	static void destroy();

	static QStringList names();
	static QStringList ownerNames();
	static QStringList greetings();
	static QStringList accepts();
	static QStringList rejects();
	static QStringList successes();
	static QStringList fails();
	static QStringList errors();

private:
	static QStringList valuesList(const QString &section);

	static QSettings *m_settings;

};

#endif // CONFIGURATION_H
