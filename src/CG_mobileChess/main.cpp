#include "CG_login.h"
#include "CG_user.h"
#include "CG_dbManager.h"
#include "CG_board.h"
#include "CG_serverConnection.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include "cg_pieceimage.h"
/***************************************************************************
 * Author:                                                        ChessGames
 * Date Created:                                                  11/07/2014
 * Date Last Modified:                                            3/28/2015
 * File Name:                                                   src/main.cpp
 *
 * Overview:
 * •	We worked on and mostly completed our database design with an Entity
 *      Relationship Diagram, SQL script for creating the database which we
 *      later converted into SQLite and sample inserts.
 *
 * •	Connected user to login system and deployed a “Hello World!”
 *      application to and Android device.
 *
 * •	Set up the game lobby and the server. This had a foundation for
 *      different game pools (1 minute, 5 minute, or 30 minute games).
 *
 * •	Converted over to QML for our presentation layer.
 *
 * •	Created a game window with a board being displayed and the basic
 *      layout of the board itself, with piece movements and sounds.
 *
 * •	Created a loading screen to transition into game.
 *
 * •	Validated piece movements, added piece dragging / zooming, cleaned
 *      up layout.
 *
 * •	Implemented chess clocks.
 *
 * •	Created a history class to review moves at the end of a game.
 *
 * •	Created a settings page currently to change country flags in the
 *      game window.
 **************************************************************************/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //Set up the database manager (Persistence Layer)
    CG_dbManager db_manager("/../../bin/chessgames.db");

    //Set up the chessgames user (Business Layer)
    CG_user cg_user(&db_manager);

    //Set up the board
    CG_board cg_board;

    QLabel validator_feedback;
    CG_validator cg_validator(validator_feedback);

    CG_serverConnection cg_serverConnection;

    engine.rootContext()->setContextProperty("User", &cg_user);
    engine.rootContext()->setContextProperty("Validator", &cg_validator);
    engine.rootContext()->setContextProperty("BoardLogic", &cg_board);
    engine.rootContext()->setContextProperty("ServerConnection", &cg_serverConnection);
    engine.addImageProvider(QLatin1String("pieces"), new CG_PieceImage(":/images/cg_pieces.png"));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
