#ifndef JARVIS_H
#define JARVIS_H

#include <QTimer>
#include <QObject>

class Ears;
class Brain;
class Voice;
class VoiceEngine;

class Jarvis : public QObject{

	Q_OBJECT

public:
	Jarvis(QObject *parent = nullptr);
	~Jarvis();

private slots:
	void processVoiceRequest(const QString &filename);
	void reactionOnText(const QString &text);

private:
	void createEars();
	void createVoice();
	void createBrain();

private:
	Ears* m_pEars;
	Brain* m_pBrain;
	Voice* m_pVoice;
};

#endif // JARVIS_H
