#ifndef VOICEENGINE_H
#define VOICEENGINE_H

#include <QString>
#include <QObject>
#include <QtMultimedia>

class VoiceEngine: QObject{
	Q_OBJECT
private:
	QString m_language;
	QMediaPlayer *m_player;
    QNetworkAccessManager *m_manager;

public:
	VoiceEngine(QString language, QObject *parent = 0);
	void setLanguage(QString language);
    Q_INVOKABLE void say(QString text);

private slots:
	void errorSlot();
	void state(QMediaPlayer::State state);
    void finished();

signals:
	void stopped();
	void error();
};

#endif // VOICEENGINE_H
