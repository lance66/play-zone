#include "CG_login.h"
#include "CG_user.h"
#include "CG_dbManager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget win;
    win.setWindowTitle("Chessgames");
    win.setStyleSheet("background-color: #448ed3");

    //Set up the database manager (Persistence Layer)
    CG_dbManager db_manager(QDir::currentPath() + "/chessgames.db");

    //Set up the chessgames user (Business Layer)
    CG_user cg_user(&db_manager);

    //Set up the login widget (Part of the Presentation Layer)
    CG_login login(&cg_user, &win);

    QGridLayout win_layout;
    win_layout.addWidget(&login);

    win.setLayout(&win_layout);

    //Default size (Just for testing purposes)
    win.resize(400, 600);
    win.show();

    return a.exec();
}
