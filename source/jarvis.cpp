#include <QDebug>

#include "ears.h"
#include "voice.h"
#include "brain.h"
#include "jarvis.h"
#include "voiceengine.h"
#include "configuration.h"

Jarvis::Jarvis(QObject *parent) : QObject(parent){
	Configuration::checkConfig();
	Configuration::fetchConfiguration();

	createEars();
	createVoice();
	createBrain();

	m_pVoice->say(m_pBrain->greetingToOwner());
}

Jarvis::~Jarvis(){
	Configuration::destroy();
}

void Jarvis::reactionOnText(const QString &text){
	qDebug() << "...matched text: " << text;

	if(m_pBrain->isName(text)){
		m_pVoice->say(m_pBrain->yesString());
	}
}

void Jarvis::createEars(){
	m_pEars = new Ears(this);
	connect(m_pEars, SIGNAL(understood(QString)), m_pVoice, SLOT(recognize(QString)));
}

void Jarvis::createVoice(){
	m_pVoice = new Voice(this);
	connect(m_pVoice, SIGNAL(matchedText(QString)), this, SLOT(reactionOnText(QString)));
}

void Jarvis::createBrain(){
	m_pBrain = new Brain(this);
}

