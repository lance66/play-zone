/************************************************************************
* File Name: CG_lobby.qml
*
* Overview:
*   This QML file is the presentation layer of our lobby screen.
*
*   A user can either select a game time for a
*       - 1 minute game
*       - 5 minute game
*       - 30 minute game
*   Or select the Logout or Settings option.
*
*   A local clock is displayed next to the user info, which includes a
*       - Username
*       - ELO Rating
*
************************************************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtMultimedia 5.0
import QtWebView 1.0
import "CG_definitions.js" as Definitions

Item
{
    id: root
    width: 400
    height: 600

    signal goBack
    signal startOneMinuteGame
    signal startFiveMinuteGame
    signal startThirtyMinuteGame
    signal settings

    // The individual control height is 1/8 of the total height.
    function getControlHeight()
    {
        return background.height / 8
    }

    // The individual control width is 100% of the smallest orientation.
    function getControlWidth()
    {
        return getSmallestOrientation() * 0.9
    }

    ColumnLayout
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.fill: parent

        RowLayout
        {
            Layout.alignment: Qt.AlignTop && Qt.AlignHCenter
            Layout.preferredWidth: getControlWidth()
            Layout.preferredHeight: getBackgroundHeight() * 0.33

            Clock
            {
                city: "Klamath Falls"
                shift: -8
            }

            ColumnLayout
            {
                Layout.alignment: Qt.AlignRight

                Text
                {
                    id: lbl_username
                    text: root.visible == true ? User.getUsername() : ""

                    color: "white"
                    font.family: customFont.name
                    font.bold: true
                    style: Text.Raised
                    styleColor: "black"

                    // Adjusts font size for scalability
                    font.pixelSize: getControlWidth() * 0.1
                }

                Text
                {
                    id: lbl_eloRating
                    text: root.visible == true ? ("ELO: " + User.getCurrentELO()) : ""

                    color: "white"
                    font.family: "Helvetica"
                    font.bold: true
                    style: Text.Raised
                    styleColor: "black"

                    // Adjusts font size for scalability
                    font.pixelSize: getControlWidth() * 0.09
                }
            }
        }

        Button
        {
            id: btn_oneMinuteGame
            text: "One Minute"
            style: cgButtonStyle

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: getControlWidth()
            Layout.preferredHeight: getControlHeight()

            onClicked:
            {
                root.startOneMinuteGame()
            }
        }

        Button
        {
            id: btn_fiveMinuteGame
            text: "Five Minute"
            style: cgButtonStyle

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: getControlWidth()
            Layout.preferredHeight: getControlHeight()

            onClicked:
            {
                root.startFiveMinuteGame()
            }
        }

        Button
        {
            id: btn_thirtyMinuteGame
            text: "Thirty Minute"
            style: cgButtonStyle

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: getControlWidth()
            Layout.preferredHeight: getControlHeight()

            onClicked:
            {
                root.startThirtyMinuteGame()
            }
        }

        RowLayout
        {
            Layout.alignment: Qt.AlignBottom && Qt.AlignHCenter

            Button
            {
                id: btn_logout
                text: "Logout"
                style: cgButtonStyle

                Layout.preferredWidth: getControlWidth() / 2
                Layout.preferredHeight: getControlHeight()

                onClicked: root.goBack()
            }

            Button
            {
                id: btn_settings
                text: "Settings"
                style: cgButtonStyle

                Layout.preferredWidth: getControlWidth() / 2
                Layout.preferredHeight: getControlHeight()

                onClicked: root.settings()
            }
        }
    }

    Component
    {
        id: cgButtonStyle

        ButtonStyle
        {
            background: Rectangle
            {
                gradient: Gradient
                {
                    GradientStop { position: 0.0; color: control.pressed ? Definitions.BUTTON_COLOR_ON_CLICK : Definitions.TOP_COLOR_FOR_BUTTON }
                    GradientStop { position: 0.5; color: control.pressed ? Definitions.BUTTON_COLOR_ON_CLICK : Definitions.BOTTOM_COLOR_FOR_BUTTON }
                }

                border.color: "#448ed3"
                smooth: true
                radius: 100
            }

            label: Text {
                font.pixelSize: getSmallestOrientation() * 0.1

                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: customFont.name
                color: "black"

                text: control.text
            }
        }
    }
}
