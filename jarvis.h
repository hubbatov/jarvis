#ifndef JARVIS_H
#define JARVIS_H

#include <QTimer>
#include <QObject>

class Ears;
class VoiceProcessor;
class VoiceEngine;

class Jarvis : public QObject{

    Q_OBJECT

public:
    Jarvis(QObject *parent = nullptr);
    ~Jarvis();

private slots:
    void processVoice(const QString &filename);
    void processVoiceFinal(const QString &text);

private:
    void createEars();
    void createVoiceProcessor();
    void createVoiceEngine();

private:
    Ears* m_pEars;
    VoiceProcessor* m_pVoiceProcessor;
    VoiceEngine* m_pVoiceEngine;
};

#endif // JARVIS_H
