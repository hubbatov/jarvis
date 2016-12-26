#include <QtQml>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <QGuiApplication>

#include "jarvis.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

#if 0
	QQmlApplicationEngine engine;
	qmlRegisterType<Jarvis>("hubbatov.jarvis", 1, 0, "Jarvis");
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#else
	Jarvis j;
#endif
	int retCode = app.exec();

	return retCode;
}
