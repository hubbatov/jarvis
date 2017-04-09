#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QDomDocument>

#include "configuration.h"
#include "wikipediasearcher.h"

WikipediaSearcher::WikipediaSearcher(QObject *parent) : BaseSearcher(parent){
}

WikipediaSearcher::~WikipediaSearcher(){
}

QString WikipediaSearcher::search(const QString &text){
	QNetworkRequest request;
	request.setUrl(Configuration::wikipediaQuery()
				   .arg(text));

	qDebug() << request.url();

	QNetworkReply* reply = get(request);
	connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(searchFinished(QNetworkReply*)));
}

void WikipediaSearcher::searchFinished(QNetworkReply *reply){
	if(reply->isFinished()){
		QString getReply ;
		getReply = reply->readAll();
		getReply = getReply.remove("\n");
		QDomDocument doc;
		if(doc.setContent(getReply)){
			QDomElement root = doc.documentElement();
			for(int i = 0; i < root.childNodes().size(); ++i){
				QDomElement suggestionElement = root.childNodes().at(i).toElement();

				qDebug() << "#" << suggestionElement.tagName();

				if(suggestionElement.tagName() == "Section"){
					QDomElement sectionElement = suggestionElement.toElement();
					if(sectionElement.childNodes().isEmpty()){
						return;
					}

					QDomElement itemElement = sectionElement.childNodes().at(0).toElement();

					for(int j = 0; j < itemElement.childNodes().size(); ++j){

						QDomElement itemPropElement = itemElement.childNodes().at(j).toElement();
						qDebug() << "##" << itemPropElement.tagName();

						if(itemPropElement.tagName() == "Description"){
							emit resultReceived(itemPropElement.text());
							return;
						}
					}
				}
			}

		}else{
			qDebug() << "Error match at wikipedia";
		}
	}
}
