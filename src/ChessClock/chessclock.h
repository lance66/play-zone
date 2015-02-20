#ifndef CHESSCLOCK_H
#define CHESSCLOCK_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QDebug>

typedef enum TimeControl
{
    ONE_MINUTE = 1,
    FIVE_MINUTE = 5,
    THIRTY_MINUTE = 30
} TimeControl;

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

   public slots:
    void setDisplay();
    void startClock();
    void stopClock();
    void resetClock(TimeControl timecontrol);

private:
QTimer* timer;
QTime*  timeValue;

};

#endif
