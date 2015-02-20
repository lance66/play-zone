#include "chessclock.h"

//Constructors
ChessClock::ChessClock(QWidget * parentWidget,int minutes,int seconds)
{
    //Create timer to countdown the clock
    timer = new QTimer();

    //Create the actual clock
    timeValue = new QTime(0,minutes,seconds);

    //Location of clock
    this->setParent(parentWidget);

    //Display the time
    this->display(timeValue->toString());

    //Updates clock
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(setDisplay()));

}

ChessClock::~ChessClock()
{
    //Delete data members we dynamically allocated
    delete timer;
    delete timeValue;
}

//Member functions
void ChessClock::startClock()
{
    this->timer->start();
}

void ChessClock::stopClock()
{
    this->timer->stop();
}

void ChessClock::resetClock(TimeControl timeControl)
{
    //Reset clock to time control
    switch(timeControl)
    {
    case ONE_MINUTE:
        this->timeValue->setHMS(0,1,0);
        this->setDisplay();
        break;

    case FIVE_MINUTE:
        this->timeValue->setHMS(0,5,0);
        this->setDisplay();
        break;

    case THIRTY_MINUTE:
        this->timeValue->setHMS(0,30,0);
        this->setDisplay();
        break;

    default:
        qDebug() << "Invalid time control. ";
        break;
    }
}

//Mutators
void ChessClock::setTimerStart(int time)
{
    this->timer->start(time);
}

void ChessClock::setDisplay()
{
  this->timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
  this->display(this->timeValue->toString());
}

QTime * ChessClock::getTimeValue()
{
    return this->timeValue;
}
