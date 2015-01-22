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
import "."

ApplicationWindow {
    id: background
    visible: true
    width: 400
    height: 600
    title: qsTr("Mobile Chess")
    color: "#448ed3"

    function getBackgroundWidth()
    {
        return background.width
    }

    function getBackgroundHeight()
    {
        return background.height
    }

    function getSmallestOrientation()
    {
        return background.width < background.height ? background.width : background.height
    }

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
        visible: false
    }
}
