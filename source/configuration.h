#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QSettings>

class Configuration{
public:
	Configuration();

	static void checkConfig();

	static QString speechLanguage();
	static QString speechQuery();
	static QString speechKey();
	static int attentionSeconds();

	static QString searchQuery();
	static QString searchKey();
	static QString searchUser();

	static QString wikipediaQuery();
	static QString wikipediaWhoPrefix();
	static QString wikipediaWhatPrefix();

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

	static QString commandType(const QString &request);

private:
	static QStringList valuesList(const QString &section, const QString neededKey = QString());

	static QSettings *m_settings;

};

#endif // CONFIGURATION_H
