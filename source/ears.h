#ifndef EARS_H
#define EARS_H

#include <QObject>

class EarsEngine;
class QAudioInput;
class QAudioRecorder;

class Ears : public QObject{

	Q_OBJECT

public:
	Ears(QObject* parent = nullptr);
	~Ears();

private slots:
	void soundDetected();
	void recordMade();

private:
	void createEarsEngine();

signals:
	void understood(const QString &filename);

private:
	QAudioRecorder *m_pRecorder;
	EarsEngine* m_pEarsEngine;
	QAudioInput* m_pEars;
	QByteArray m_earsBuffer;
};

#endif // EARS_H
