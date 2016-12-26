#ifndef BRAIN_H
#define BRAIN_H

#include <QObject>

class Vocabulary;

class Brain : public QObject {

	Q_OBJECT

public:
	Brain(QObject *parent = 0);
	~Brain();

	bool isJarvisName(const QString &request);
	bool isGreeting(const QString &request);

	Vocabulary* vocabulary() const;

protected:
	QStringList toRequests(const QString &request);

private:
	bool m_attention;
	Vocabulary* m_pVocabulary;

};

#endif // BRAIN_H
