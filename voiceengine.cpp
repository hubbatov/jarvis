#include <QDir>

#include "voiceengine.h"
#include "configuration.h"

VoiceEngine::VoiceEngine(QString language){

    m_manager = new QNetworkAccessManager(this);
	m_language = language;
    m_player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    m_player->setVolume(100);

	QObject::connect(m_player, SIGNAL(error(QMediaPlayer::Error)),
					 this, SLOT(errorSlot()));
	QObject::connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
					 this, SLOT(errorSlot()));
}

void VoiceEngine::setLanguage(QString language){
	m_language = language;
}

void VoiceEngine::say(QString text){
    QString path = QString("https://tts.voicetech.yandex.net/generate?text=%1&format=mp3&lang=%2&speaker=zahar&key=%3")
            .arg(text)
            .arg(m_language)
            .arg(Configuration::apiKey());

    qDebug() << path;

    const QUrl requestUrl(path);
    QNetworkRequest request(requestUrl);

    QNetworkReply* reply = m_manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(finished()));
}

void VoiceEngine::errorSlot(){
	emit error();
}

void VoiceEngine::state(QMediaPlayer::State state){
	if (state == QMediaPlayer::StoppedState)
        emit stopped();
}

void VoiceEngine::finished(){
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
}
