#include <QDateTime>

#include "vocabulary.h"
#include "configuration.h"

Vocabulary::Vocabulary(){
	m_selfNames = Configuration::names();
	m_ownerNames = Configuration::ownerNames();
	m_greetings = Configuration::greetings();
	m_accepts = Configuration::accepts();
	m_rejects = Configuration::rejects();
	m_succeses = Configuration::successes();
	m_fails = Configuration::fails();
	m_errors = Configuration::errors();
}

QString Vocabulary::owner(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());
	int index = (int) (rand() % m_ownerNames.size());
	return m_ownerNames[index];
}

QString Vocabulary::greeting(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());

	int greetIndex = (int) (rand() % m_greetings.size());
	int ownerIndex = (int) (rand() % m_ownerNames.size());

	return m_greetings[greetIndex] + "," + m_ownerNames[ownerIndex];
}

QString Vocabulary::yes(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());
	int index = (int) (rand() % m_accepts.size());
	return m_accepts[index];
}

QString Vocabulary::no(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());
	int index = (int) (rand() % m_rejects.size());
	return m_rejects[index];
}

QString Vocabulary::success(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());
	int index = (int) (rand() % m_succeses.size());
	return m_succeses[index];
}

QString Vocabulary::fail(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());
	int index = (int) (rand() % m_fails.size());
	return m_fails[index];
}

QString Vocabulary::error(){
	srand(QDateTime::currentDateTime().time().msecsSinceStartOfDay());
	int index = (int) (rand() % m_errors.size());
	return m_errors[index];
}
