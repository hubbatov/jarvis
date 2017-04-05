#ifndef BRAIN_H
#define BRAIN_H

#include <QTimer>
#include <QObject>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

class Vocabulary;

class Brain : public QNetworkAccessManager {

	Q_OBJECT

public:
	Brain(QObject *parent = 0);
	~Brain();

	bool isJarvisName(const QString &request);
	bool isGreeting(const QString &request);
	bool isListening();

	Vocabulary* vocabulary() const;

	QString tryRecorgnizeCommand(const QString &text);
	bool doCommand(const QString &command);

public slots:
	void payAttention();
    void sleep();

protected:
	QStringList toRequests(const QString &request);

private:
    bool m_attention;
	QTimer m_attentionTimer;
	Vocabulary* m_pVocabulary;
};

#endif // BRAIN_H
