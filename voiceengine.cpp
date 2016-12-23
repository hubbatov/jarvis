#include "voiceengine.h"

VoiceEngine::VoiceEngine(QString language){
	m_url = "http://translate.google.com/translate_tts?ie=UTF-8&tl=%1&q=%2&key=AIzaSyAqk7vE0vQDR3JItUPgFp6bcPqgJz8h8tI";

	m_language = language;

	m_playlist = new QMediaPlaylist;

	m_player = new QMediaPlayer;

	QObject::connect(m_player, SIGNAL(error(QMediaPlayer::Error)),
					 this, SLOT(errorSlot()));
	QObject::connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
					 this, SLOT(errorSlot()));
}

void VoiceEngine::setLanguage(QString language){
	m_language = language;
}

void VoiceEngine::speech(QString text){
	if (QMultimedia::Available == 0)  {
		QString i;
		text.replace(" ","+");
		m_playlist->addMedia(QUrl(m_url.arg(m_language).arg(text)));
		m_player->setPlaylist(m_playlist);
		m_player->play();
	} else {
		emit error();
	}

}

void VoiceEngine::errorSlot(){
	emit error();
}

void VoiceEngine::state(QMediaPlayer::State state){
	if (state == QMediaPlayer::StoppedState)
		emit stopped();
}
