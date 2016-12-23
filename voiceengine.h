#ifndef VOICEENGINE_H
#define VOICEENGINE_H

#include <QString>
#include <QObject>
#include <QtMultimedia>

class VoiceEngine: QObject{
	Q_OBJECT
private:
	QString m_language;
	QMediaPlaylist *m_playlist;
	QMediaPlayer *m_player;
	QString m_url;
public:
	VoiceEngine(QString language);
	void setLanguage(QString language);
	Q_INVOKABLE void speech(QString text);

private slots:
	void errorSlot();
	void state(QMediaPlayer::State state);
signals:
	void stopped();
	void error();
};

#endif // VOICEENGINE_H
