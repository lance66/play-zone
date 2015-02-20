#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>
#include "chessclock.h"

enum
{
    WHITE = 0,
    BLACK = 1
};

int main(int argc, char *argv[])
{
    //Initialize app and window
    QApplication app(argc, argv);
    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    window->setWindowTitle(QString::fromUtf8("Chess Clock"));
    window->resize(500, 500);

    //Create widget for clock
    QWidget *whiteWidget = new QWidget(window);
    QWidget *blackWidget = new QWidget(window);
    QPushButton *btn_start = new QPushButton("Start");
    QPushButton *btn_stop = new QPushButton("Stop");
    QPushButton *btn_reset = new QPushButton("Reset");

    layout->addWidget(blackWidget);
    layout->addWidget(whiteWidget);
    layout->addWidget(btn_start);
    layout->addWidget(btn_stop);
    layout->addWidget(btn_reset);
    layout->setAlignment(layout, Qt::AlignHCenter);

    btn_start->setFixedSize(45,45);
    btn_stop->setFixedSize(45,45);
    btn_reset->setFixedSize(45,45);

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

    bool turn = WHITE;

    //Observer pattern to connect buttons to functions
    QObject::connect(btn_start, SIGNAL(clicked()), whiteClock, SLOT(startClock()));
    QObject::connect(btn_stop, SIGNAL(clicked()), turn ? blackClock : whiteClock, SLOT(stopClock()));
    QObject::connect(whiteClock, SIGNAL(toggleTurn()), blackClock, SLOT(startClock()));
    QObject::connect(btn_reset, SIGNAL(clicked()), blackClock, SLOT(resetClock()));

    //Start app
    return app.exec();
}
