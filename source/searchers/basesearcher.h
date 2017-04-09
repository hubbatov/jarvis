#ifndef BASE_SEARCHER_H
#define BASE_SEARCHER_H

#include <QNetworkAccessManager>

class BaseSearcher : public QNetworkAccessManager {
	Q_OBJECT

public:
	BaseSearcher(QObject * parent = 0) : QNetworkAccessManager(parent) {}
	~BaseSearcher(){}

	virtual QString search(const QString &request) = 0;

signals:
	void resultReceived(const QString &text);
};

#endif
