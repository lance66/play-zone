import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtMultimedia 5.0
import QtQuick.Dialogs 1.1

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

        anchors.top: parent.top
        anchors.left: parent.left

        height: getBackgroundHeight() * (1/6)

        Image
        {
            id: img_opponentFlag
            source: "images/cg_flag_turkey.png"
            width: getSmallestOrientation() * 0.175
            height: getSmallestOrientation() * 0.175

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

            horizontalAlignment: Text.AlignRight
            width: 100
        }
    }

    // Board / Clocks
    CG_board
    {
        id: cg_board
        width: root.setBoardSize()
        height: root.setBoardSize()

        anchors.left: isLandscape() === false ? parent.left : rowDrawAndResign.left

        y: getBackgroundHeight() * (1/6)
    }

    // Opponent LED / Clock
    Row
    {
        anchors.right: parent.right
        anchors.top: cg_board.top

        Rectangle
        {
            id: rect_opponentLED
            width: getSmallestOrientation() * 0.04
            height: getSmallestOrientation() * 0.04
            radius: width * 0.5
            color: cg_board.whiteBlackMove == 1 ? "#00FF00" : "#FFFFFF"
        }

        CG_clock
        {
            id: cg_opponentClock

            width: getSmallestOrientation() * 0.2
            height: width * (172/475)

            running:
            {
                if (cg_board.whiteBlackMove == 1 && root.visible == true)
                    true
                else
                    false
            }
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
            color: cg_board.whiteBlackMove == 0 ? "#00FF00" : "#FFFFFF"
        }

        CG_clock
        {
            id: cg_playerClock

            width: getSmallestOrientation() * 0.2
            height: width * (172/475)

            running:
            {
                if (cg_board.whiteBlackMove == 0 && root.visible == true)
                    true
                else
                    false
            }
        }
    }

    // Player Info
    Row
    {
        id: rowPlayerInfo

        anchors.top: cg_board.bottom
        anchors.left: parent.left

        height: getBackgroundHeight() * (1/6)

        Image
        {
            id: img_player_map
            source: "images/cg_flag_unitedStates.png"
            width: getSmallestOrientation() * 0.175
            height: getSmallestOrientation() * 0.175

            anchors.verticalCenter: parent.verticalCenter
        }

        Text
        {
            id: lbl_username
            text: root.visible == true ? (User.getUsername() + "  " + User.getCurrentELO()) : ""

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
            horizontalAlignment: Text.AlignRight
            width: 100
        }
    }

    // Draw / Resign buttons and notation
    Row
    {
        id: rowDrawAndResign

        height: getBackgroundHeight() * (1/6)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: rowPlayerInfo.bottom

        spacing: getSmallestOrientation() * 0.04

        Button
        {
            id: btn_draw
            style: cgButtonStyle

            width: getSmallestOrientation() * 0.1
            height: getSmallestOrientation() * 0.1

            Image
            {
                source: "images/cg_draw.png"
                width: getSmallestOrientation() * 0.05
                height: getSmallestOrientation() * 0.05

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            onClicked:
            {
                //Flash client screen green with sound effect

                //Flash opponent's screen green with sound effect
                //Flash for ten seconds or until opponent makes move
                root.finished()
            }

            anchors.verticalCenter: parent.verticalCenter
        }

        Text
        {
            id: lbl_notation
            text: "1.Nf3"

            color: "white"
            font.family: "Helvetica"
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            // Adjusts font size for scalability
            font.pixelSize:  getSmallestOrientation() * 0.04

            anchors.verticalCenter: parent.verticalCenter
        }

        Audio
        {
            id: iPod
            source: "Sounds/resign.mp3"
            autoLoad: true
        }

        Button
        {
            id: btn_resign
            style: cgRedButtonStyle

            width: getSmallestOrientation() * 0.1
            height: getSmallestOrientation() * 0.1

            Image
            {
                source: "images/cg_resign.png"
                width: getSmallestOrientation() * 0.05
                height: getSmallestOrientation() * 0.05

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }



            onClicked:
            {
                //Post results
                lbl_player_result.visible = true
                lbl_player_result.text = "0"
                lbl_player_result.color = "yellow"
                lbl_player_result.font.family = "Helvetica"
                lbl_player_result.font.bold = true
                lbl_player_result.font.pixelSize = getSmallestOrientation() * 0.1

                //Post results
                lbl_opponentResult.visible = true
                lbl_opponentResult.text = "1"
                lbl_opponentResult.color = "yellow"
                lbl_opponentResult.font.family = "Helvetica"
                lbl_opponentResult.font.bold = true
                lbl_opponentResult.font.pixelSize = getSmallestOrientation() * 0.1

                //Sound effect to notify user of resignation
                iPod.play()

                //Notify user game is over and how many ELO points were gained/lost
                resignDialog.open()

                //When user presses OK or close, bring him back to the lobby.
                //root.finished()
            }

            anchors.verticalCenter: parent.verticalCenter
        }

    }

    MessageDialog
    {
        id: resignDialog
        title: "Game Over"
        text: "You resigned against " + lbl_opponent.text.toString()
        onAccepted:
        {
            console.log(":(")
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

    Component
    {
        id: cgRedButtonStyle

        ButtonStyle
        {
            background: Rectangle {
                gradient: Gradient {
                    GradientStop { position: 0.0; color: control.pressed ? "#AA1111" : "#FF5555" }
                    GradientStop { position: 0.5; color: control.pressed ? "#FF5555" : "#AA1111" }
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

    /**************************************************************
    *	  Purpose:  Returns the appropriate size the chessboard
    *               should be.
    *
    *     Entry:    User has entered a game.
    *
    *     Exit:     The chessboard is set to the appropriate size.
    ****************************************************************/

    function setBoardSize()
    {
        return getBackgroundHeight() / 2
    }
}
