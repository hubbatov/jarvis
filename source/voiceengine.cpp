#include <QDir>

#include "voiceengine.h"
#include "configuration.h"

VoiceEngine::VoiceEngine(QObject *parent) : QObject(parent){

	m_busy = false;
	m_manager = new QNetworkAccessManager(this);
	m_player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
	m_player->setVolume(100);

	QObject::connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
					 this, SLOT(mediaStateChanged(QMediaPlayer::State)));
}

void VoiceEngine::say(QString text){
	m_toSayList.append(text);
	sayNext();
}

void VoiceEngine::sayNext(){
	if(m_busy || m_toSayList.isEmpty())
		return;

	m_busy = true;

	QString text = m_toSayList.first();

	QString path = QString(Configuration::speechQuery())
			.arg(text)
			.arg(Configuration::speechLanguage())
			.arg(Configuration::speechKey());

	const QUrl requestUrl(path);
	QNetworkRequest request(requestUrl);

	QNetworkReply* reply = m_manager->get(request);
	connect(reply, SIGNAL(finished()), this, SLOT(audioReceived()));
}

void VoiceEngine::mediaStateChanged(QMediaPlayer::State state){
	if(state == QMediaPlayer::StoppedState){
		m_player->setMedia(QUrl::fromLocalFile(""));
		QTimer::singleShot(1000, this, SLOT(sayNext()));
	}
}

void VoiceEngine::state(QMediaPlayer::State state){
	if (state == QMediaPlayer::StoppedState)
		emit stopped();
}

void VoiceEngine::audioReceived(){
	m_toSayList.removeFirst();

	QNetworkReply *reply = dynamic_cast<QNetworkReply*>(sender());
	QByteArray data = reply->readAll();

	QString path = QString("%1/.jarvis/responce.mp3").arg(QDir::homePath());
	QFile f(path);
	f.open(QIODevice::WriteOnly);
	QDataStream ds(&f);
	ds << data;
	f.close();

	m_player->setMedia(QUrl::fromLocalFile(path));
	m_player->play();

	m_busy = false;
}
