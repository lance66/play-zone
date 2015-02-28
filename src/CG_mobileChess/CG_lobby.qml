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

Item
{
    id: root
    width: 400
    height: 600

    signal goBack
    signal startOneMinuteGame
    signal startFiveMinuteGame
    signal startThirtyMinuteGame

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

    Audio
    {
        id: iPod
        source: "Sounds/01 - Untitled (Album Version).mp3"
        autoLoad: true
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
                    font.family: "Chocolate Dealer"
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
                iPod.play()
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
                iPod.play()
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
                iPod.play()
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

                onClicked: root.goBack()
            }
        }
    }

    Component
    {
        id: cgButtonStyle

        ButtonStyle
        {
            background: Rectangle {
                gradient: Gradient {
                    GradientStop { position: 0.0; color: control.pressed ? "#b6ee65" : "#76ae25" }
                    GradientStop { position: 0.5; color: control.pressed ? "#76ae25" : "#b6ee65" }
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
                font.family: "Chocolate Dealer"
                color: "black"

                text: control.text
            }
        }
    }
}
