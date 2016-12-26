#include <QDir>
#include <QUrl>
#include <QTimer>
#include <QAudioInput>
#include <QAudioRecorder>

#include "ears.h"
#include "earsengine.h"

const int SampleSize = 4096;

Ears::Ears(QObject *parent) : QObject(parent){
	m_pEars = nullptr;
	m_pEarsEngine = nullptr;

	QAudioEncoderSettings settings;
	settings.setCodec("audio/pcm");
	settings.setQuality(QMultimedia::HighQuality);

	m_pRecorder = new QAudioRecorder(this);
	m_pRecorder->setEncodingSettings(settings);

	createEarsEngine();
}

Ears::~Ears(){
	m_pEars->stop();
	m_pEarsEngine->stop();
}

void Ears::listenMore(){
	if (!m_pEars)
		return;

	qint64 len = m_pEars->bytesReady();
	if (len > SampleSize)
		len = SampleSize;
	qint64 l = m_pEarsEngine->read(m_earsBuffer.data(), len);
	if (l > 0)
		m_pEarsEngine->write(m_earsBuffer.constData(), l);
}

void Ears::soundDetected(){
	if(m_pEarsEngine->level() > 0.5 && m_pRecorder->state() != QAudioRecorder::RecordingState){
		m_pRecorder->record();
		QString path = QString("%1/.jarvis/request.wav").arg(QDir::homePath());
		m_pRecorder->setProperty("path", path);
		m_pRecorder->setOutputLocation(QUrl::fromLocalFile(path));
		QTimer::singleShot(3000, this, SLOT(recordMade()));
	}
}

void Ears::recordMade(){
	QString path = m_pRecorder->property("path").toString();
	m_pRecorder->stop();
	emit understood(path);
}

void Ears::createEarsEngine(){
	QAudioFormat format;
	format.setSampleRate(44100);
	format.setChannelCount(2);
	format.setSampleSize(16);
	format.setSampleType(QAudioFormat::SignedInt);
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setCodec("audio/pcm");

	QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
	if (!info.isFormatSupported(format)) {
		qWarning() << "Default format not supported - trying to use nearest";
		format = info.nearestFormat(format);
	}

	if(m_pEarsEngine)
		delete m_pEarsEngine;
	if(m_pEars)
		delete m_pEars;

	m_pEarsEngine = new EarsEngine(format, this);

	m_pEars = new QAudioInput(format, this);
	m_pEarsEngine->start();
	m_pEars->start(m_pEarsEngine);
	connect(m_pEarsEngine, SIGNAL(readyRead()), this, SLOT(listenMore()));
	connect(m_pEarsEngine, SIGNAL(update()), SLOT(soundDetected()));
}
