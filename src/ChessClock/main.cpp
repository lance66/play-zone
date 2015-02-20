#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include "chessclock.h"

int main(int argc, char *argv[])
{
    //Initialize app and window
    QApplication app(argc, argv);
    QMainWindow *window = new QMainWindow();

    window->setWindowTitle(QString::fromUtf8("Chess Clock"));
    window->resize(250, 250);

    //Create widget for clock
    QWidget *whiteWidget = new QWidget(window);
    QWidget *blackWidget = new QWidget(window);

    //Start counting down from 5 minutes
    ChessClock *whiteClock = new ChessClock(whiteWidget,5,0);
    ChessClock *blackClock = new ChessClock(blackWidget, 5 ,0);

    //Format clocks
    whiteClock->setFixedSize(245, 245);
    blackClock->setFixedSize(245, 245);
    blackClock->setStyleSheet("color: green");

    window->setCentralWidget(whiteWidget);
    window->setCentralWidget(blackWidget);

    //Display clocks
    window->show();

    //Countdown by 1 second
    whiteClock->setTimerStart(1000);
    blackClock->setTimerStart(1000);

    //Start app
    return app.exec();
}
