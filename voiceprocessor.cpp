#include <QUrl>
#include <QUuid>
#include <QFile>
#include <QDebug>

#include <QDomDocument>

#include <QNetworkReply>
#include <QNetworkRequest>

#include "configuration.h"
#include "voiceprocessor.h"

QString VoiceProcessor::contentType = "audio/x-wav";
QString VoiceProcessor::url = "http://asr.yandex.net/asr_xml?uuid=%1&topic=queries&lang=%2&key=%3";

VoiceProcessor::VoiceProcessor(QObject* parent)
	: QObject(parent){
	m_pNetworkManager = new QNetworkAccessManager(this);
}

void VoiceProcessor::recognize(const QString &filename){
    QString uuid = QUuid::createUuid().toString();
    uuid.remove("{");
    uuid.remove("}");
    uuid.remove("-");

    const QUrl requestUrl(url
                          .arg(uuid)
                          .arg(Configuration::language())
                          .arg(Configuration::apiKey()));

    qDebug() << requestUrl.toString();

    QNetworkRequest req(requestUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QFile *compressedFile = new QFile(filename);
	compressedFile->open(QIODevice::ReadOnly);
    QNetworkReply *reply = m_pNetworkManager->post(req, compressedFile);
    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));
}

void VoiceProcessor::cancel(){
}

void VoiceProcessor::replyFinished() {
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    parseResponse(reply);
}

void VoiceProcessor::parseResponse(QIODevice* reply){
	QString getReply ;
	getReply = reply->readAll();

    qDebug() << "The Reply " << getReply;

    QDomDocument doc;
    qDebug() << "Reply is XML:" << doc.setContent(getReply);

    QStringList resultList;

    QDomElement root = doc.documentElement();
    for(int i = 0; i < root.childNodes().size(); ++i){
        resultList.append(root.childNodes().at(i).toElement().text().toLower());
    }

    setResults(resultList.join(","));
    emit finished(results());
}

void VoiceProcessor::setResults(const QString &results){
	if(m_results == results)
		return;
	m_results = results;
	emit resultsChanged();
}

QString VoiceProcessor::results()const{
    return m_results;
}
