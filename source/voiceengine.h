#ifndef VOICEENGINE_H
#define VOICEENGINE_H

#include <QString>
#include <QObject>
#include <QtMultimedia>

class VoiceEngine: QObject{
	Q_OBJECT
private:
	QStringList m_toSayList;
	QMediaPlayer *m_player;
	QNetworkAccessManager *m_manager;
	bool m_busy;

public:
	VoiceEngine(QObject *parent = 0);

	Q_INVOKABLE void say(QString text);

private slots:
	void mediaStateChanged(QMediaPlayer::State state);
	void state(QMediaPlayer::State state);
	void audioReceived();
	void sayNext();

signals:
	void stopped();
	void error();
};

#endif // VOICEENGINE_H
