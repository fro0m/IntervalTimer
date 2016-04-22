#ifndef FTIMER_H
#define FTIMER_H
#include <QTimer>
#include <QQueue>
#include <QString>
#include <QDebug>


class FTimer : public QTimer
{
    Q_OBJECT
    Q_PROPERTY(QString inputString READ inputString WRITE setInputString NOTIFY inputStringChanged)
    Q_PROPERTY(qint32 msecsDisplay READ msecsDisplay WRITE setMsecsDisplay NOTIFY msecsDisplayChanged)
    Q_PROPERTY(int currentTimerIndex READ currentTimerIndex WRITE setCurrentTimerIndex NOTIFY currentTimerIndexChanged)
public:
    FTimer(QObject *parent = Q_NULLPTR);
    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    Q_INVOKABLE int timersCount() const;
    Q_INVOKABLE int getSecs(const int timerIndex) const;

    qint32 msecsDisplay() const;
    QString inputString() const;

    int currentTimerIndex() const;

public slots:
    void setMsecsDisplay(qint32 msecsDisplay);
    void setInputString(QString inputString);

    void setCurrentTimerIndex(int currentTimerIndex);

signals:
    void msecsDisplayChanged(qint32 msecsDisplay);
    void inputStringChanged(QString inputString);
    void started();

    void currentTimerIndexChanged(int currentTimerIndex);

private:
    qint32 m_msecsDisplay = 0;
    QString m_inputString = QStringLiteral("");
    QQueue<qint32> timers;
    int m_currentTimerIndex = {-1};

    bool parseInput();
    bool processTimersSequence();

private slots:
    void updateDisplayText();

};


#endif // FTIMER_H
