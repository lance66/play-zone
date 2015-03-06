import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtMultimedia 5.0
import QtQuick.Dialogs 1.1
import "CG_definitions.js" as Definitions

Item
{
    id: root
    width: 400
    height: 600

    signal finished
    property int gameTimeInMinutes: 1
    property string currentMove: ".Nf3"

    //Functions
    function getCurrentMove()
    {
        return currentMove
    }

    function setCurrentMove(string)
    {
        currentMove = string
    }

    CG_banner
    {
        id: cg_opponent
        width: getBannerWidth()
        height: getBannerHeight()

        countryFlag: "images/cg_flag_turkey.png"
        playerInfo: "Trudodyr\n2715"
        ledActive: cg_board.whiteBlackMove == 1 ? true : false

        clockRunning:
        {
            if (cg_board.whiteBlackMove == 1 && root.visible == true)
                true
            else
                false
        }

        anchors.top: parent.top
        anchors.left: parent.left
    }

    CG_banner
    {
        id: cg_player
        width: getBannerWidth()
        height: getBannerHeight()

        countryFlag: "images/cg_flag_unitedStates.png"
        playerInfo: root.visible == true ? (User.getUsername() + "\n" + User.getCurrentELO()) : ""
        ledActive: cg_board.whiteBlackMove == 0 ? true : false

        clockRunning:
        {
            if (cg_board.whiteBlackMove == 0 && root.visible == true)
                true
            else
                false
        }

        anchors.bottom: isLandscape() ? parent.bottom : undefined
        anchors.top: isPortrait() ? cg_board.bottom : undefined
        anchors.left: parent.left
    }

    // Board / Clocks
    CG_board
    {
        id: cg_board
        width: root.setBoardSize()
        height: root.setBoardSize()

        //anchors.left: isLandscape() === false ? parent.left : rowPlayerInfo.right
        anchors.top: isPortrait() ? cg_opponent.bottom : parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    // Draw / Resign buttons and notation
    Button
    {
        id: btn_draw
        style: cgButtonStyle

        width: isPortrait() ? getBannerHeight() : getBannerHeight() / 4
        height: isPortrait() ? getBannerHeight() : getBannerHeight() / 4

        anchors.left: isLandscape() ? cg_board.right : cg_board.left
        anchors.top: isLandscape() ? root.top : cg_player.bottom

        Image
        {
            source: "images/cg_draw.png"
            width: parent.width * 0.5
            height: parent.height * 0.5

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        onClicked:
        {
            //Flash client screen green with sound effect

            //Flash opponent's screen green with sound effect
            //Flash for ten seconds or until opponent makes move
            setCurrentMove("1...c5")

            root.finished()
        }
    }

    Text
    {
        id: lbl_notation
        text: getCurrentMove()

        color: "white"
        font.family: "Helvetica"
        font.bold: true
        style: Text.Raised
        styleColor: "black"

        // Adjusts font size for scalability
        font.pixelSize:  getSmallestOrientation() * 0.04

        anchors.verticalCenter: isLandscape() ? parent.verticalCenter : undefined
        anchors.left: isLandscape() ? cg_board.right : undefined

        anchors.horizontalCenter: isPortrait() ? parent.horizontalCenter : undefined
        anchors.top: isPortrait() ? cg_player.bottom : undefined
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

        width: isPortrait() ? getBannerHeight() : getBannerHeight() / 4
        height: isPortrait() ? getBannerHeight() : getBannerHeight() / 4

        anchors.left: isLandscape() ? cg_board.right : lbl_notation.right
        anchors.bottom: isLandscape() ? parent.bottom : undefined
        anchors.top: isPortrait() ? cg_player.bottom : undefined

        Image
        {
            source: "images/cg_resign.png"
            width: parent.width * 0.5
            height: parent.height * 0.5

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        onClicked:
        {
            //Post results
            cg_player.result = "0"
            cg_player.resultVisible = true

            //Post results
            cg_opponent.result = "1"
            cg_opponent.resultVisible = true

            //Sound effect to notify user of resignation
            iPod.play()

            //Notify user game is over and how many ELO points were gained/lost
            resignDialog.open()

            //Stop the clocks from running
            cg_opponent.clockRunning = false
            cg_player.clockRunning = false

            //When user presses OK or close, bring him back to the lobby.
            //root.finished()
        }
    }

    MessageDialog
    {
        id: resignDialog
        title: "Game Over"
        text: "You resigned against " + cg_opponent.playerInfo.toString()
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
                font.family: "Chocolate Dealer"
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
                font.family: "Chocolate Dealer"
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
        if (!isLandscape())
            return getBackgroundWidth()
        else
            return getBackgroundHeight()
    }

    function getBannerHeight()
    {
        if (!isLandscape())
            return (getBackgroundHeight() - getBackgroundWidth()) / 3
        else
            return getBackgroundHeight() / 2
    }

    function getBannerWidth()
    {
        if (!isLandscape())
            return getBackgroundWidth()
        else
            return (getBackgroundWidth() - getBackgroundHeight()) / 2
    }
}
