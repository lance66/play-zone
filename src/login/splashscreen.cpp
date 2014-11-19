#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent) :
    QWidget(parent)
{
    gl_splashScreen.addWidget(&lbl_welcome);
    setLayout(&gl_splashScreen);
}

SplashScreen::SplashScreen(QString username, QWidget *parent) :
    QWidget(parent), lbl_welcome("Hello, " + username  + "!")
{
    gl_splashScreen.addWidget(&lbl_welcome);
    setLayout(&gl_splashScreen);
}
