import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtMultimedia 5.0
import QtQuick.Dialogs 1.1
import "CG_board.js" as Board
import "CG_definitions.js" as Definitions
import "CG_game.js" as Game

Item
{
    id: root
    width: 400
    height: 600

    signal finished
    property int gameTimeInMinutes: 1
    property bool gameOver: false

    CG_banner
    {
        id: cg_opponent
        width: Game.getBannerWidth()
        height: Game.getBannerHeight()

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
        width: Game.getBannerWidth()
        height: Game.getBannerHeight()

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
        width: Game.getBoardSize()
        height: Game.getBoardSize()

        //anchors.left: isLandscape() === false ? parent.left : rowPlayerInfo.right
        anchors.top: isPortrait() ? cg_opponent.bottom : parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    // Draw / Resign buttons and notation
    Button
    {
        id: btn_draw
        style: cgButtonStyle

        width: isPortrait() ? Game.getBannerHeight() : Game.getBannerHeight() / 3
        height: isPortrait() ? Game.getBannerHeight() : Game.getBannerHeight() / 3

        anchors.left: isLandscape() ? undefined : cg_board.left
        anchors.right: isLandscape() ? root.right : undefined
        anchors.top: isLandscape() ? root.top : cg_player.bottom

        Image
        {
            source: gameOver == false ? "images/cg_draw.png" : "images/cg_leftArrow.png"
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

            //Go backward throughout the game.

            cg_board.currentMoveNumber = Board.backward(cg_board.listOfMoves, cg_board.currentMoveNumber)
            iPod2.play()

            //root.finished()
        }
    }

    Text
    {
        id: lbl_notation
        text: Board.current(cg_board.listOfMoves, cg_board.currentMoveNumber)

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

    Audio
    {
        id: iPod2
        source: "Sounds/move.mp3"
        autoLoad: true
        volume: 1.0
    }

    Button
    {
        id: btn_resign
        style: cgRedButtonStyle

        width: isPortrait() ? Game.getBannerHeight() : Game.getBannerHeight() / 3
        height: isPortrait() ? Game.getBannerHeight() : Game.getBannerHeight() / 3

        anchors.right: isLandscape() ? root.right : cg_board.right
        anchors.bottom: isLandscape() ? parent.bottom : undefined
        anchors.top: isPortrait() ? cg_player.bottom : undefined

        Image
        {
            source: gameOver == false ? "images/cg_resign.png" : "images/cg_rightArrow.png"
            width: parent.width * 0.5
            height: parent.height * 0.5

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        onClicked:
        {

            if(gameOver == false)
            {
                //If someone resigned, the game is over
                gameOver = true

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
            }
            else
                cg_board.currentMoveNumber = Board.forward(cg_board.listOfMoves, cg_board.currentMoveNumber)
                iPod2.play()

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
}
