#include "CG_login.h"
#include "CG_user.h"
#include "CG_dbManager.h"
#include <QApplication>

/***************************************************************************
 * Author:                                                        ChessGames
 * Date Created:                                                  11/07/2014
 * Date Last Modified:                                            12/01/2014
 * File Name:                                                   src/main.cpp
 *
 * Overview: Creates the foundation for our login application. Sets up the
 * database manager (Persistence Layer), chessgames user (Business Layer),
 * login widget (forms part of our Presentation Layer), and resizes our
 * window for our testing purposes.
 *
 * Input: Requires a valid username, password, and email for registration.
 * If user is already registered then the user simply enters a username, and
 * password. All usernames must follow a certain guideline as outlined by
 * the validation the user will see when main is executing. Such validations
 * include no double spaces, etc.
 *
 * Output: Displays the window, with the size that is specified, along with
 * QLineEdits where the username, password, email for inputs, along with
 * two buttons, one for registering an account, and the other for loggin in.
 **************************************************************************/

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
