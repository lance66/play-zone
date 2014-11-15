#include "splashscreen.h"
#include "ui_splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);
}

SplashScreen::SplashScreen(QString username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);
    ui->lbl_welcome->setText("Hello, " + username + "!");
}

SplashScreen::~SplashScreen()
{
    delete ui;
}
