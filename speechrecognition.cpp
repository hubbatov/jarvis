#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QSslSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "speechrecognition.h"

const char* SpeechRecognition::kContentType = "audio/x-flac; rate=44100";
const char* SpeechRecognition::kUrl = "https://www.google.com/speech-api/v2/recognize?output=json&lang=ru-ru&key=AIzaSyAqk7vE0vQDR3JItUPgFp6bcPqgJz8h8tI";

SpeechRecognition::SpeechRecognition(QObject* parent)
	: QObject(parent){
	m_pNetworkManager = new QNetworkAccessManager(this);
}

void SpeechRecognition::start(){
	const QUrl url(kUrl);
	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, kContentType);
	req.setAttribute(QNetworkRequest::DoNotBufferUploadDataAttribute, false);
	req.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
					 QNetworkRequest::AlwaysNetwork);
	QFile *compressedFile = new QFile("E:/Samples/hello.flac");
	compressedFile->open(QIODevice::ReadOnly);
	m_pReply = m_pNetworkManager->post(req, compressedFile);
	connect(m_pReply, SIGNAL(finished()), this, SLOT(replyFinished()));
}

void SpeechRecognition::replyFinished() {

	Result result = Result_ErrorNetwork;
	Hypotheses hypotheses;

	if (m_pReply->error() != QNetworkReply::NoError) {
		qDebug() << "ERROR \n" << m_pReply->errorString();
	} else {
		qDebug() << "Running ParserResponse for \n" << m_pReply << result;
		parseResponse(m_pReply, &result, &hypotheses);
	}
	emit finished(result, hypotheses);
	m_pReply->deleteLater();
	m_pReply = NULL;
}

void SpeechRecognition::parseResponse(QIODevice* reply, Result* result,
									  Hypotheses* hypotheses){
	QString getReply ;
	getReply = reply->readAll();

	getReply = getReply.mid(14); //странно почему возвращается 2 результата. приходится один выпиливать

	qDebug() << "The Reply " << getReply;

	QJsonDocument jsonDoc = QJsonDocument::fromJson(getReply.toUtf8());

	QStringList values;

	if(jsonDoc.isObject()){
		QJsonArray resultArray = jsonDoc.object().value("result").toArray().first().toObject().value("alternative").toArray();

		for(int i = 0; i < resultArray.size(); ++i){
			Hypothesis h;
			h.transcript = resultArray.at(i).toObject().value("transcript").toString();
			h.confidence = resultArray.at(i).toObject().value("confidence").toDouble();

			qDebug() << h.transcript << h.confidence;

			values.append(h.transcript);
			hypotheses->append(h);
		}

		setResults(QString(values.join(",")));
	}
}

void SpeechRecognition::setResults(const QString &results){
	if(m_results == results)
		return;
	m_results = results;
	emit resultsChanged();
}

QString SpeechRecognition::results()const{
	return m_results;
}
