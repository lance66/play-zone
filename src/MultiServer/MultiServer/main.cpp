#include <QtCore/QCoreApplication>
#include "myserver.h"

/***************************************************************************
 * Author:                                                        ChessGames
 * Date Created:                                                  01/01/2014
 * Date Last Modified:                                            01/11/2014
 * File Name:                                       src/multiserver/main.cpp
 *
 * Overview: Creates the foundation of the networking portion for our
 * application. Sets up the server, so that we can connect to the localhost.
 * from a client. Once server is running, message is displayed saying the
 * server started, and is listening for connections.
 *
 * Input: Requires the user to connect using a client. Telnet serves as the
 * client for this application, as a means of sending messages to the
 * server.
 *
 * Output: Displays the messages that are being sent from the client on the
 * server console window.
 **************************************************************************/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer Server;

    // Starts the server, so that it can listen for incoming connections
    Server.StartServer();

    return a.exec();
}
