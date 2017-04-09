#include <QUrl>
#include <QUuid>
#include <QFile>
#include <QDebug>

#include <QDomDocument>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "voice.h"
#include "voiceengine.h"
#include "configuration.h"

QString Voice::contentType = "audio/x-wav";
QString Voice::url = "http://asr.yandex.net/asr_xml?uuid=%1&topic=queries&lang=%2&key=%3";

Voice::Voice(QObject* parent)
	: QObject(parent){
	m_pNetworkManager = new QNetworkAccessManager(this);
	m_pVoiceEngine = new VoiceEngine(this);
}

void Voice::recognize(const QString &filename){
	QString uuid = QUuid::createUuid().toString();
	uuid.remove("{");
	uuid.remove("}");
	uuid.remove("-");

	const QUrl requestUrl(url
						  .arg(uuid)
						  .arg(Configuration::speechLanguage())
						  .arg(Configuration::speechKey()));

	QNetworkRequest req(requestUrl);
	req.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

	QFile *compressedFile = new QFile(filename);
	compressedFile->open(QIODevice::ReadOnly);
	QNetworkReply *reply = m_pNetworkManager->post(req, compressedFile);
    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
}

void Voice::say(const QString &text){
	m_pVoiceEngine->say(text);
}

void Voice::replyFinished() {
	QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
	parseResponse(reply);
}

void Voice::parseResponse(QIODevice* reply){
	QString getReply ;
	getReply = reply->readAll();

	QDomDocument doc;
	doc.setContent(getReply);

	QStringList resultList;

	QDomElement root = doc.documentElement();
	for(int i = 0; i < root.childNodes().size(); ++i){
		resultList.append(root.childNodes().at(i).toElement().text().toLower());
	}

	setResults(resultList.join(","));
	emit matchedText(results());
}

void Voice::setResults(const QString &results){
	if(m_results == results)
		return;
	m_results = results;
	emit resultsChanged();
}

QString Voice::results()const{
	return m_results;
}
