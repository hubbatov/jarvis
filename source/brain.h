#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>
#include <QStringList>

class Brain : public QObject {

	Q_OBJECT

public:
	Brain(QObject *parent = 0);
	~Brain();

	bool isName(const QString &request);
	bool isGreetingString(const QString &request);

	QString greetingToOwner();
	QString yesString();
	QString noString();

protected:
	QStringList parseRequest(const QString &request);

private:
	QStringList m_selfNames;
	QStringList m_ownerNames;
	QStringList m_greetings;
	QStringList m_accepts;
	QStringList m_rejects;

};

#endif // BRAIN_H
