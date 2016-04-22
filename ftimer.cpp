#include "ftimer.h"


FTimer::FTimer(QObject *parent) : QTimer(parent), m_inputString("35*6+10+30*7")
{

    connect(this, &FTimer::timeout, this, &FTimer::updateDisplayText);
    //qDebug() << this->isSingleShot();
}

void FTimer::start()
{
    //qDebug() << "start() is called";//! dbg
    if (!m_inputString.isEmpty()) {
        if(parseInput()) {
            processTimersSequence();
        }
    }
}

void FTimer::pause()
{

}

void FTimer::stop()
{

}

int FTimer::timersCount() const
{
    return timers.size();
}

int FTimer::getSecs(const int timerIndex) const
{
    //qDebug() << "timerIndex";
    if (timerIndex >= 0 && timerIndex < timers.size())
        return timers.at(timerIndex);
    else
        return 0;
}

qint32 FTimer::msecsDisplay() const
{
    return m_msecsDisplay;
}

QString FTimer::inputString() const
{
    return m_inputString;
}

int FTimer::currentTimerIndex() const
{
    return m_currentTimerIndex;
}

void FTimer::setMsecsDisplay(qint32 msecsDisplay)
{
    if (m_msecsDisplay == msecsDisplay)
        return;

    m_msecsDisplay = msecsDisplay;
    emit msecsDisplayChanged(msecsDisplay);
}

void FTimer::setInputString(QString inputString)
{
    if (m_inputString == inputString)
        return;

    m_inputString = inputString;
    emit inputStringChanged(inputString);
}

void FTimer::setCurrentTimerIndex(int currentTimerIndex)
{
    if (m_currentTimerIndex == currentTimerIndex)
        return;

    m_currentTimerIndex = currentTimerIndex;
    emit currentTimerIndexChanged(currentTimerIndex);
}

bool FTimer::parseInput()
{
    qint32 timerIntervalMsecs = 0;
    qint32 multiplicationValue = 0;
    uint order = 1;
    bool readMultiplicationValue = false;
    for (int it = 0; it < m_inputString.length(); it++) {
        //timerIntervalMsecs = 0;
        //multiplicationValue = 0;
        const char currentChar = m_inputString.at(it).cell();
        //bool flagOfLastIncrement = false;
        switch (currentChar) {
        case '*':
            if (timerIntervalMsecs) {
                readMultiplicationValue = true;
                order = 1;
            }
            break;
        case '+':
            if (timerIntervalMsecs) {
                do {
                    timers.enqueue(timerIntervalMsecs);
                } while(--multiplicationValue > 0);
                //                for(int it = 0; it <= multiplicationValue; it++) {
                //                    timers.enqueue(timerIntervalMsecs);
                //                }
                multiplicationValue = 0;
                order = 1;
                timerIntervalMsecs = 0;
                readMultiplicationValue = false;
            }
            break;
        default:
            if (currentChar >= 48 && currentChar <= 57) {
                if (readMultiplicationValue) {
                    multiplicationValue = multiplicationValue * order
                            + (currentChar - 48);
                } else {
                    timerIntervalMsecs = timerIntervalMsecs * order
                            + (currentChar - 48);
                }
                order *= 10;
            }
        }
    }
    if (timerIntervalMsecs) {
        do {
            timers.enqueue(timerIntervalMsecs);
        } while(--multiplicationValue > 0);
    }
    return true;
}

bool FTimer::processTimersSequence()
{
    QTimer::start(500);
    emit started();
    setCurrentTimerIndex(m_currentTimerIndex + 1);

    //setInterval(500);
//    for (qint32 currentTimerMsecs : timers) {
//        while (currentTimerMsecs - remainingTime)
//    }
    return true;
}

void FTimer::updateDisplayText()
{
    static int repeats = 0;
    static int timerIndex = 0;
    qint32 currentTimerMsecs = timers.at(timerIndex);
    qint32 timeValue = currentTimerMsecs - repeats * 0.5;
    setMsecsDisplay(timeValue);
    if(timeValue <= 0) {//! FIXME bug unlimited timer.
        repeats = 0;
        emit started();
        setCurrentTimerIndex(m_currentTimerIndex + 1);
        if (timerIndex < timers.length() - 1) {
            timerIndex++;
        } else {
            QTimer::stop();
            return;
        }
    }
    repeats++;
}



