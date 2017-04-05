#include <QDir>
#include <QDebug>
#include <QTextCodec>

#include "configuration.h"

QString configDir = QString("%1/.jarvis").arg(QDir::homePath());
QString pathToConfig = configDir + "/" + "config.ini";

QSettings* Configuration::m_settings = nullptr;

QStringList Configuration::valuesList(const QString &section, const QString neededKey){
	QStringList result;
	if(Configuration::m_settings){
		Configuration::m_settings->beginGroup(section);

		QStringList keys = Configuration::m_settings->allKeys();
		foreach (QString key, keys) {
			if(neededKey.isEmpty() || key == neededKey)
				result.append(Configuration::m_settings->value(key).toString());
		}

		Configuration::m_settings->endGroup();
	}
	return result;
}

Configuration::Configuration(){
}

void Configuration::checkConfig(){
	QDir confDir(configDir);
	if(!confDir.exists())
		confDir.mkpath(configDir);

	QFile conf(pathToConfig);
	if(!conf.exists()){
		conf.open(QIODevice::WriteOnly);
		conf.write(QByteArray("[api]\n"));
		conf.write(QByteArray("[jarvis-names]\n"));
		conf.write(QByteArray("[your-names]\n"));
		conf.write(QByteArray("[greetings]\n"));
		conf.write(QByteArray("[accepts]\n"));
		conf.write(QByteArray("[rejects]\n"));
		conf.write(QByteArray("[fails]\n"));
		conf.write(QByteArray("[errors]\n"));
		conf.write(QByteArray("[commands]\n"));

		conf.close();
	}
}

QString Configuration::language(){
	if(m_settings)
		return m_settings->value("api/language").toString();
	return QString();
}

QString Configuration::apiKey(){
	if(m_settings)
		return m_settings->value("api/key").toString();
	return QString();
}

int Configuration::attentionSeconds(){
	if(m_settings)
		return m_settings->value("api/attention").toInt();
	return 60;
}

void Configuration::fetchConfiguration(){
	m_settings = new QSettings(pathToConfig, QSettings::IniFormat);
}

void Configuration::destroy(){
	delete m_settings;
}

QStringList Configuration::names(){
	return valuesList("jarvis-names");
}

QStringList Configuration::ownerNames(){
	return valuesList("your-names");
}

QStringList Configuration::greetings(){
	return valuesList("greetings");
}

QStringList Configuration::accepts(){
	return valuesList("accepts");
}

QStringList Configuration::rejects(){
	return valuesList("rejects");
}

QStringList Configuration::successes(){
	return valuesList("successes");
}

QStringList Configuration::fails(){
	return valuesList("fails");
}

QStringList Configuration::errors(){
	return valuesList("errors");
}

QString Configuration::commandType(const QString &request){
	m_settings->beginGroup("commands");
	foreach (const QString &key, m_settings->allKeys()) {
		QString value = m_settings->value(key).toString();

		QStringList data = value.split("#");

		if(data.last() == request && !request.isEmpty()){
			m_settings->endGroup();
			return data.first();
		}
	}
	m_settings->endGroup();
	return "undefined";
}
