#include <QDebug>

#include "brain.h"
#include "vocabulary.h"
#include "configuration.h"

Brain::Brain(QObject *parent) : QObject(parent){
	m_pVocabulary = new Vocabulary;
	m_attentionTimer.setSingleShot(true);
    connect(&m_attentionTimer, SIGNAL(timeout()), this, SLOT(sleep()));
}

Brain::~Brain(){
	delete m_pVocabulary;
}

bool Brain::isJarvisName(const QString &request){
	QStringList requests = toRequests(request);

	foreach (QString name, m_pVocabulary->selfNames()) {
		foreach (QString supposedName, requests) {
			if(name == supposedName)
				return true;
		}
	}
	return false;
}

bool Brain::isGreeting(const QString &request){
	QStringList requests = toRequests(request);

	foreach (QString greet, m_pVocabulary->greetings()) {
		foreach (QString supposedGreeting, requests) {
			if(greet == supposedGreeting)
				return true;
		}
	}
	return false;
}

bool Brain::isCommand(const QString &request){
	return false;
}

bool Brain::isListening(){
    return m_attention;
}

QStringList Brain::toRequests(const QString &request){
	QStringList requests;
	if(request.contains(","))
		requests = request.split(",");
	else requests.append(request);

	return requests;
}

Vocabulary *Brain::vocabulary() const{
	return m_pVocabulary;
}

void Brain::payAttention(){
    m_attentionTimer.start(Configuration::attentionSeconds() * 1000);
    m_attention = true;
}

void Brain::sleep(){
    qDebug() << "...jarvis not listen anymore";
    m_attention = false;
}




