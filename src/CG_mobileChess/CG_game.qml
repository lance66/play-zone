import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtMultimedia 5.0
import QtQuick.Dialogs 1.2
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
    property alias playerFlagFrame: cg_player.flagFrame
    property string opponentName: "Trudodyr"
    property int opponentELO: 2715
    property bool color: false //White

    Connections
    {
        target: ServerConnection
        onOpponentReceived:
        {
            opponentName = ServerConnection.getOpponent();
            opponentELO = ServerConnection.getOpponentELO()
            color = ServerConnection.getColor();
        }
        onNetworkPlayerMoved:
        {
            BoardLogic.move(fromFile, fromRank, toFile, toRank)
            cg_board.whiteBlackMove = !cg_board.whiteBlackMove;
            Board.refreshBoard(cg_board.pieces)
        }
    }

    CG_banner
    {
        id: cg_opponent
        width: Game.getBannerWidth()
        height: Game.getBannerHeight()

        playerInfo: opponentName + "\n" + opponentELO
        ledActive: cg_board.whiteBlackMove == 1 ? true : false
        flagFrame: 21

        clockRunning:
        {
            //If it's black's turn and the game is active.
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

        x:
        {
            if (isLandscape())
                getBackgroundWidth() - width
            else
                width
        }

        y:
        {
            if (isLandscape())
                0
            else
                getBackgroundHeight() - height
        }

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

            if (cg_board.currentMoveNumber - 1 >= 0)
            {
                cg_board.currentMoveNumber = Board.backward(cg_board.listOfMoves, cg_board.currentMoveNumber)
                BoardLogic.callHistoryBackward()
                Board.refreshBoard(cg_board.pieces)
                iPod2.play()
            }
            else
                resignDialog.open()

            //Make the starting and ending selections invisible when
            //traversing the history.
            cg_board.startingMove.visible = false
            cg_board.endingMove.visible = false
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
        font.pixelSize:  getSmallestOrientation() * 0.08

        x:
        {
            if (isLandscape())
                getBackgroundWidth() - lbl_notation.width
            else
                (getBackgroundWidth() / 2) - (lbl_notation.width / 2)
        }

        y:
        {
            if (isLandscape())
                (getBackgroundHeight() / 2) - (lbl_notation.height / 2)
            else
                getBackgroundHeight() - (btn_resign.height / 2) - (lbl_notation.height / 2)
        }
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
        source: "Sounds/wrongMove.mp3"
        autoLoad: true
        volume: 1.0
    }

    Button
    {
        id: btn_resign
        style: cgRedButtonStyle

        width: isPortrait() ? Game.getBannerHeight() : Game.getBannerHeight() / 3
        height: isPortrait() ? Game.getBannerHeight() : Game.getBannerHeight() / 3

        x:
        {
            if (isLandscape())
                getBackgroundWidth() - width
            else
                getBackgroundWidth() - (width * 2)
        }

        y: getBackgroundHeight() - height

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
            {
                cg_board.currentMoveNumber = Board.forward(cg_board.listOfMoves, cg_board.currentMoveNumber)
                BoardLogic.callHistoryForward()
                Board.refreshBoard(cg_board.pieces)
                iPod2.play()
            }
        }
    }

    MessageDialog
    {
        id: resignDialog
        title: "Game Over"
        text: "You resigned against:\n\n" + cg_opponent.playerInfo + "\n\nDo you wish to review the game?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: resignDialog.close()
        onNo:
        {
            //Reset the presentation and business layer
            BoardLogic.resetBoard()
            Board.refreshBoard(cg_board.pieces)
            gameOver = false

            resignDialog.close()
            root.finished()
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
        id: cgButtonStyle2

        ButtonStyle
        {
            background: Rectangle
            {
                gradient: Gradient
                {
                    GradientStop { position: 0.0; color: control.pressed ? Definitions.BUTTON_COLOR_ON_CLICK : Definitions.TOP_COLOR_FOR_BUTTON }//"#b6ee65" : "#76ae25" }
                    GradientStop { position: 0.5; color: control.pressed ? Definitions.BUTTON_COLOR_ON_CLICK : Definitions.BOTTOM_COLOR_FOR_BUTTON /*"#fbdb65"*/ }//"#76ae25" : "#b6ee65" }
                }

                border.color: "#1c375b" //"#448ed3"
                border.width: 4
                smooth: true
                radius: width * 0.5
            }

            label: Text
            {
                font.pixelSize: 30

                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: customFont.name
                color: "#000000" //"#CCFFFF"

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
