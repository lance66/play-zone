#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWindow>
#include "chessclock.h"
#include "match.h"

int main(int argc, char *argv[])
{
    //Initialize app and window
    QApplication app(argc, argv);
    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QVBoxLayout *layout2 = new QVBoxLayout;

    layout->addLayout(layout2);

    window->setWindowTitle(QString::fromUtf8("Chess Clock"));
    window->resize(600, 600);

    //Create widget for clock
    QWidget *whiteWidget = new QWidget(window);
    QWidget *blackWidget = new QWidget(window);
    QPushButton *btn_start = new QPushButton("Start");
    QPushButton *btn_stopWhite = new QPushButton("Stop");
    QPushButton *btn_stopBlack = new QPushButton("Stop");
    QPushButton *btn_reset = new QPushButton("Reset");
    QRadioButton *btn_ledWhite = new QRadioButton;
    QRadioButton *btn_ledBlack = new QRadioButton;


    //Black is always no top, so add it's widget first
    layout->addWidget(blackWidget);
    layout->addWidget(whiteWidget);
    layout->addWidget(btn_start);
    layout->addWidget(btn_stopBlack);
    layout->addWidget(btn_stopWhite);
    layout->addWidget(btn_reset);
    layout->setAlignment(layout, Qt::AlignHCenter);

    //Add LEDs to horizontal layout
    layout2->addWidget(btn_ledWhite);
    layout2->addWidget(btn_ledBlack);

    btn_start->setFixedSize(45,45);
    btn_stopWhite->setFixedSize(45,45);
    btn_stopBlack->setFixedSize(45,45);
    btn_reset->setFixedSize(45,45);
    btn_ledWhite->setFixedSize(25,25);
    btn_ledBlack->setFixedSize(25,25);

    //Start counting down from 5 minutes
    ChessClock *whiteClock = new ChessClock(whiteWidget,5,0);
    ChessClock *blackClock = new ChessClock(blackWidget, 5 ,0);

    //Format clocks
    whiteClock->setFixedSize(200, 200);
    blackClock->setFixedSize(200, 200);
    blackClock->setStyleSheet("color: green");

    //Display clocks
    window->setLayout(layout);
    window->show();

    //Create match class, which will contain turn variable
    Match *match = new Match;

    //Observer pattern to connect buttons to functions

    //Start game and start white's clock
    QObject::connect(btn_start, SIGNAL(clicked()), whiteClock, SLOT(startClock()));
    QObject::connect(btn_start, SIGNAL(clicked()), whiteClock, SLOT(updateLED()));
    //QQbject::connect(whiteClock, SIGNAL(turnOnLED(QRadioButton*)),

    //White's turn = stop white's clock, black's turn = stop black's clock
    QObject::connect(btn_stopWhite, SIGNAL(clicked()), whiteClock, SLOT(stopClock()));
    QObject::connect(btn_stopBlack, SIGNAL(clicked()), blackClock, SLOT(stopClock()));

    //After white stops the clock, change turns and start black's clock
    QObject::connect(whiteClock, SIGNAL(toggleTurn()), blackClock, SLOT(startClock()));

    //Notify match class that it is now black's turn
    QObject::connect(whiteClock, SIGNAL(toggleTurn()), match, SLOT(toggleTurn()));

    //After black stops the clock, change turns and start white's clock
    QObject::connect(blackClock, SIGNAL(toggleTurn()), whiteClock, SLOT(startClock()));

    //Notify match class that turn has changed
    QObject::connect(blackClock, SIGNAL(toggleTurn()), match, SLOT(toggleTurn()));

    //Reset black's clock when you press the reset button
    QObject::connect(btn_reset, SIGNAL(clicked()), blackClock, SLOT(resetClock()));

    //Start app
    return app.exec();
}
