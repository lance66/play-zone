/************************************************************************
* File Name: main.qml
*
* Overview:
*   This is the Main QML file for our presentation layer. This layer
*   allows us to switch among the different screens for:
*       - Login
*       - Lobby
*       - Game
*
************************************************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: background
    visible: true
    width: 400
    height: 600
    title: qsTr("Mobile Chess")
    color: "#448ed3"

    CG_login
    {
        id: login
        anchors.fill: parent
        onLoggedIn: { login.visible = false
                      lobby.visible = true }
    }

    CG_lobby
    {
        id: lobby
        anchors.fill: parent

        onGoBack: { lobby.visible = false
                    login.visible = true }

        onStartGame: { lobby.visible = false
                       loading.visible = true
                       loading.timer.start() }

        visible: false
    }

    CG_loading
    {
        id: loading
        anchors.fill: parent

        onMatched: { loading.visible = false
                     game.visible = true }

        visible: false
    }

    CG_game
    {
        id: game
        anchors.fill: parent
        onFinished: { game.visible = false
                      lobby.visible = true }
        visible: false
    }

    /**************************************************************
    *	  Purpose:  Get the background width of the app for all
    *               that need access to it.
    *
    *     Entry:    User has opened the application.
    *
    *     Exit:     Returns the width of the application.
    ****************************************************************/

    function getBackgroundWidth()
    {
        return background.width
    }

    /**************************************************************
    *	  Purpose:  Get the background height of the app for all
    *               that need access to it.
    *
    *     Entry:    User has opened the application.
    *
    *     Exit:     Returns the height of the application.
    ****************************************************************/

    function getBackgroundHeight()
    {
        return background.height
    }

    /**************************************************************
    *	  Purpose:  Get the smallest orientation for scalability
    *               purposes, whether it's the portrait or landscape
    *               orientation.
    *
    *     Entry:    User has opened the application.
    *
    *     Exit:     Returns the smallest orientation of the
    *               application.
    ****************************************************************/

    function getSmallestOrientation()
    {
        return background.width < background.height ? background.width : background.height
    }
}
