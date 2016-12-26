#ifndef EARSENGINE_H
#define EARSENGINE_H

#include <QObject>
#include <QIODevice>
#include <QByteArray>
#include <QAudioInput>

class EarsEngine : public QIODevice {
    Q_OBJECT

public:
    EarsEngine(const QAudioFormat &format, QObject *parent);
    ~EarsEngine();

    void start();
    void stop();

    QAudioFormat audioFormat();

    qreal level() const { return m_level; }

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    const QAudioFormat m_format;
    quint32 m_maxAmplitude;
    qreal m_level;

signals:
    void update();
};

#endif // EARSENGINE_H
