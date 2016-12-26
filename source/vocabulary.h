#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QStringList>

class Vocabulary {
public:
	Vocabulary();

	QString owner();
	QString greeting();
	QString yes();
	QString no();
	QString success();
	QString fail();
	QString error();

	QStringList selfNames() const { return m_selfNames; }
	QStringList ownerNames() const { return m_ownerNames; }
	QStringList greetings() const { return m_greetings; }
	QStringList accepts() const { return m_accepts; }
	QStringList rejects() const { return m_rejects; }
	QStringList sucesses() const { return m_succeses; }
	QStringList fails() const { return m_fails; }
	QStringList errors() const { return m_errors; }

private:
	QStringList m_selfNames;
	QStringList m_ownerNames;
	QStringList m_greetings;
	QStringList m_accepts;
	QStringList m_rejects;
	QStringList m_succeses;
	QStringList m_fails;
	QStringList m_errors;
};

#endif // VOCABULARY_H
