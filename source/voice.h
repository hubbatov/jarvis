#ifndef VOICEPROCESOR_H
#define VOICEPROCESOR_H

#include <QList>
#include <QObject>

class QIODevice;
class VoiceEngine;
class QNetworkReply;
class QNetworkAccessManager;

class Voice : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString results READ results NOTIFY resultsChanged)

public:
	Voice( QObject* parent = 0);
	static QString url;
	static QString contentType;

	QString results()const;

	Q_INVOKABLE void recognize(const QString &filename);
	Q_INVOKABLE void cancel();

	Q_INVOKABLE void say(const QString &text);

	void setResults(const QString &results);

signals:
	void matchedText(const QString &matchedString);
	void resultsChanged();

private slots:
	void replyFinished();

private:
	void parseResponse(QIODevice* reply);

private:
	QString m_results;
	QNetworkAccessManager* m_pNetworkManager;
	VoiceEngine* m_pVoiceEngine;
};

#endif // VOICEPROCESOR_H
