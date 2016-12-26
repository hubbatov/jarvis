#include <QDebug>

#include "ears.h"
#include "voice.h"
#include "brain.h"
#include "jarvis.h"
#include "vocabulary.h"
#include "voiceengine.h"
#include "configuration.h"

Jarvis::Jarvis(QObject *parent) : QObject(parent){
	Configuration::checkConfig();
	Configuration::fetchConfiguration();

	createVoice();
	createEars();
	createBrain();

	m_pVoice->say(m_pBrain->vocabulary()->greeting());
	//test();
}

Jarvis::~Jarvis(){
	Configuration::destroy();
}

void Jarvis::test(){
	m_pVoice->say(m_pBrain->vocabulary()->yes() +"," + m_pBrain->vocabulary()->owner());
	m_pVoice->say(m_pBrain->vocabulary()->no() + "," + m_pBrain->vocabulary()->owner());
	m_pVoice->say(m_pBrain->vocabulary()->success());
	m_pVoice->say(m_pBrain->vocabulary()->fail());
	m_pVoice->say(m_pBrain->vocabulary()->error());
}

void Jarvis::reactionOnText(const QString &text){
	qDebug() << "...matched text: " << text;

	if(m_pBrain->isJarvisName(text)){
		m_pVoice->say(m_pBrain->vocabulary()->yes());
		m_pBrain->payAttention();
	}

	if(m_pBrain->isListening()){
		//...process commands here if Jarvis is listen to you
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

