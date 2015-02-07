import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0

Item
{
    id: root
    width: 400
    height: 600

    signal finished

    // Opponent Info
    Row
    {
        id: rowOpponentInfo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        height: getBackgroundHeight() * (1/6)

        Image
        {
            id: img_opponentFlag
            source: "images/cg_temp_flag.png"
            width: getSmallestOrientation() * 0.08
            height: getSmallestOrientation() * 0.04

            anchors.verticalCenter: parent.verticalCenter
        }

        Text
        {
            id: lbl_opponent
            text: "Trudodyr  2715"

            color: "white"
            font.family: "Helvetica"
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            // Adjusts font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.04

            anchors.verticalCenter: parent.verticalCenter

        }

        Text
        {
            id: lbl_opponentResult
            visible: false

            anchors.verticalCenter: parent.verticalCenter
        }
    }

    // Board / Clocks
    CG_board
    {
        id: cg_board
        width: getBackgroundHeight() / 2
        height: getBackgroundHeight() / 2

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: rowOpponentInfo.bottom
    }

    // Opponent LED / Clock
    Row
    {
        anchors.right: parent.right
        y: cg_board.y

        Rectangle
        {
            id: rect_opponentLED
            width: getSmallestOrientation() * 0.04
            height: getSmallestOrientation() * 0.04
            radius: width * 0.5
        }

        Text
        {
            id: lbl_opponentClock
            text: "01:00"

            color: "white"
            font.family: "Helvetica"
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            // Adjusts font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.04
        }
    }

    // Player LED / Clock
    Row
    {
        id: rowPlayerLED
        anchors.right: parent.right
        anchors.bottom: cg_board.bottom

        Rectangle
        {
            id: rect_playerLED
            width: getSmallestOrientation() * 0.04
            height: getSmallestOrientation() * 0.04
            radius: width * 0.5
        }

        Text
        {
            id: lbl_playerClock
            text: "01:00"

            color: "white"
            font.family: "Helvetica"
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            // Adjusts font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.04
        }
    }

    // Player Info
    Row
    {
        id: rowPlayerInfo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: cg_board.bottom
        height: getBackgroundHeight() * (1/6)

        Image
        {
            id: img_player_map
            source: "images/cg_temp_flag.png"
            width: getSmallestOrientation() * 0.08
            height: getSmallestOrientation() * 0.04

            anchors.verticalCenter: parent.verticalCenter
        }

        Text
        {
            id: lbl_username
            text: User.getUsername() + "  " + User.getCurrentELO()

            color: "white"
            font.family: "Helvetica"
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            // Adjusts font size for scalability
            font.pixelSize:  getSmallestOrientation() * 0.04

            anchors.verticalCenter: parent.verticalCenter
        }

        Text
        {
            id: lbl_player_result
            visible: false

            anchors.verticalCenter: parent.verticalCenter
        }
    }

    // Draw / Resign buttons and notation
    Row
    {
        id: rowDrawAndResign
        anchors.horizontalCenter: parent.horizontalCenter
        height: getBackgroundHeight() * (1/6)
        anchors.top: rowPlayerInfo.bottom

        Button
        {
            id: btn_draw
            text: "</"
            style: cgButtonStyle

            width: getSmallestOrientation() * 0.2
            height: getSmallestOrientation() * 0.2

            onClicked: root.finished()

            anchors.verticalCenter: parent.verticalCenter
        }

        Text
        {
            id: lbl_notation
            text: "1..Nf3"

            color: "white"
            font.family: "Helvetica"
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            // Adjusts font size for scalability
            font.pixelSize:  getSmallestOrientation() * 0.04

            anchors.leftMargin: getSmallestOrientation() * 0.04
            anchors.rightMargin: getSmallestOrientation() * 0.04

            anchors.verticalCenter: parent.verticalCenter
        }

        Button
        {
            id: btn_resign
            text: "X"
            style: cgButtonStyle

            width: getSmallestOrientation() * 0.2
            height: getSmallestOrientation() * 0.2

            onClicked: root.finished()

            anchors.verticalCenter: parent.verticalCenter
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
                radius: width * 0.5
            }

            label: Text {
                font.pixelSize: getSmallestOrientation() * 0.04

                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: "Helvetica"
                color: "black"

                text: control.text
            }
        }
    }
}
