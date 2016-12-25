#ifndef VOICEPROCESOR_H
#define VOICEPROCESOR_H

#include <QList>
#include <QObject>

class QIODevice;
class QNetworkAccessManager;
class QNetworkReply;

class VoiceProcessor : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString results READ results NOTIFY resultsChanged)

public:
    VoiceProcessor( QObject* parent = 0);
    static QString url;
    static QString contentType;

    QString results()const;

    Q_INVOKABLE void recognize(const QString &filename);
    Q_INVOKABLE void cancel();

	void setResults(const QString &results);

signals:
    void finished(const QString &matchedString);
	void resultsChanged();

private slots:
	void replyFinished();

private:
    void parseResponse(QIODevice* reply);

private:
	QNetworkAccessManager* m_pNetworkManager;
	QNetworkReply* m_pReply;
	QString m_results;
};

#endif // VOICEPROCESOR_H
