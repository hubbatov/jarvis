#include <QDateTime>

#include "brain.h"
#include "configuration.h"

Brain::Brain(QObject *parent) : QObject(parent){
	m_selfNames = Configuration::names();
	m_ownerNames = Configuration::ownerNames();
	m_greetings = Configuration::greetings();
	m_accepts = Configuration::accepts();
	m_rejects = Configuration::rejects();
}

Brain::~Brain(){
}

bool Brain::isName(const QString &request){
	QStringList requests = parseRequest(request);

	foreach (QString name, m_selfNames) {
		foreach (QString supposedName, requests) {
			if(name == supposedName)
				return true;
		}
	}
	return false;
}

bool Brain::isGreetingString(const QString &request){
	QStringList requests = parseRequest(request);

	foreach (QString greet, m_greetings) {
		foreach (QString supposedGreeting, requests) {
			if(greet == supposedGreeting)
				return true;
		}
	}
	return false;
}

QString Brain::greetingToOwner(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());

	int greetIndex = (int) (rand() % m_greetings.size());
	int ownerIndex = (int) (rand() % m_ownerNames.size());

	return m_greetings[greetIndex] + "," + m_ownerNames[ownerIndex];
}

QString Brain::yesString(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());
	int index = (int) (rand() % m_accepts.size());
	return m_accepts[index];
}

QString Brain::noString(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());
	int index = (int) (rand() % m_rejects.size());
	return m_rejects[index];
}

QStringList Brain::parseRequest(const QString &request){
	QStringList requests;
	if(request.contains(","))
		requests = request.split(",");
	else requests.append(request);

	return requests;
}


