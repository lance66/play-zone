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
    title: qsTr("Hello World")
    color: "#448ed3"

    function getLogoSize()
    {
        return background.height / 2
    }

    function getControlWidth()
    {
        return background.width < background.height ? (background.width * 0.9) : (background.height * 0.9)
    }

    function getControlHeight()
    {
        return background.height / 15
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
