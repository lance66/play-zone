#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget win;

    Login login(&win);
    QGridLayout win_layout;
    win_layout.addWidget(&login);

    win.setLayout(&win_layout);

    //Default size (Just for testing purposes)
    win.resize(400, 600);
    win.show();

    return a.exec();
}
