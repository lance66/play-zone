#include "CG_splashScreen.h"

CG_splashScreen::CG_splashScreen(QWidget *parent) :
    QWidget(parent)
{
    gl_splashScreen.addWidget(&lbl_welcome);
    setLayout(&gl_splashScreen);
}

CG_splashScreen::CG_splashScreen(QString username, QWidget *parent) :
    QWidget(parent), lbl_welcome("Hello, " + username  + "!")
{
    gl_splashScreen.addWidget(&lbl_welcome);
    setLayout(&gl_splashScreen);
}

void CG_splashScreen::setText(QString str)
{
    lbl_welcome.setText("Hello, " + str + "!");
}
