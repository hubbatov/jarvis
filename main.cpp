#include <QtQml>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include <QGuiApplication>

#include "voiceengine.h"
#include "speechrecognition.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;

	VoiceEngine voice("ru-RU");
	voice.speech(QString::fromUtf8("Привет"));

	qmlRegisterType<SpeechRecognition>("hubbatov.jarvis", 1, 0, "SpeechAPI");

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	int retCode = app.exec();

	return retCode;
}
