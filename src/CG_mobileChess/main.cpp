#include "CG_login.h"
#include "CG_user.h"
#include "CG_dbManager.h"
#include "CG_board.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

/***************************************************************************
 * Author:                                                        ChessGames
 * Date Created:                                                  11/07/2014
 * Date Last Modified:                                            2/15/2015
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
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //Set up the database manager (Persistence Layer)
    CG_dbManager db_manager("chessgames.db");

    //Set up the chessgames user (Business Layer)
    CG_user cg_user(&db_manager);

    //Set up the board
    CG_board cg_board;

    QLabel validator_feedback;
    CG_validator cg_validator(validator_feedback);

    engine.rootContext()->setContextProperty("User", &cg_user);
    engine.rootContext()->setContextProperty("Validator", &cg_validator);
    engine.rootContext()->setContextProperty("Board", &cg_board);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
