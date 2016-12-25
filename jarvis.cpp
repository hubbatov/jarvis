#include <QDebug>

#include "ears.h"
#include "jarvis.h"
#include "voiceengine.h"
#include "configuration.h"
#include "voiceprocessor.h"

Jarvis::Jarvis(QObject *parent) : QObject(parent){
    createEars();
    createVoiceProcessor();
    createVoiceEngine();
}

Jarvis::~Jarvis(){
}

void Jarvis::processVoice(const QString &filename){
    qDebug() << "...processing request";
    m_pVoiceProcessor->recognize(filename);
}

void Jarvis::processVoiceFinal(const QString &text){
    qDebug() << "..matched text: " << text;

    QStringList matchedTexts;
    if(text.contains(","))
        matchedTexts = text.split(",");
    else
        matchedTexts.append(text);

    if(matchedTexts.contains(QString::fromUtf8("джарвис"))){
        m_pVoiceEngine->say("Да,сээр");
    }
    if(matchedTexts.contains(QString::fromUtf8("привет"))){
        m_pVoiceEngine->say("Здравствуйте,сээр");
    }
}

void Jarvis::createEars(){
    m_pEars = new Ears(this);

    connect(m_pEars, SIGNAL(understood(QString)), this, SLOT(processVoice(QString)));
}

void Jarvis::createVoiceProcessor(){
    m_pVoiceProcessor = new VoiceProcessor(this);
    connect(m_pVoiceProcessor, SIGNAL(finished(QString)), this, SLOT(processVoiceFinal(QString)));
}

void Jarvis::createVoiceEngine(){
    m_pVoiceEngine = new VoiceEngine(Configuration::language());
}
