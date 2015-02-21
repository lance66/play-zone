#ifndef CHESSCLOCK_H
#define CHESSCLOCK_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QRadioButton>

typedef enum TimeControl
{
    ONE_MINUTE = 1,
    FIVE_MINUTE = 5,
    THIRTY_MINUTE = 30
} TimeControl;

typedef enum STATE_LED
{
    OFF = 0,
    ON = 1
} STATE_LED;

class ChessClock: public QLCDNumber
{
    Q_OBJECT

public:

    //Constructors
    ChessClock(QWidget * parentWidget,int minutes,int seconds);
    ~ChessClock();

    //Member functions

    //Mutators
    void setTimerStart(int time);

    QTime * getTimeValue();
    bool getTurn();

public slots:
    void resetClock(TimeControl timeControl = FIVE_MINUTE);
    void setDisplay();
    void startClock();
    void stopClock();
    void updateLED();

signals:
    void toggleTurn();
    void turnOnLED(QRadioButton *);

private:
    QTimer* timer;
    QTime*  timeValue;
    bool m_turn;
    bool m_led;
};

#endif
