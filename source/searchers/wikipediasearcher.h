#ifndef WIKIPEDIA_SEARCHER_H
#define WIKIPEDIA_SEARCHER_H

#include "basesearcher.h"

class WikipediaSearcher : public BaseSearcher {
	Q_OBJECT

public:
	WikipediaSearcher(QObject *parent = 0);
	~WikipediaSearcher();

	QString search(const QString &text);

private slots:
	void searchFinished(QNetworkReply *);
};

#endif
