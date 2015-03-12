import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtMultimedia 5.0
import "CG_board.js" as Board

Item
{
    id: root

    property bool starting_position: false
    property int starting_index: -1
    property int ending_index: -1
    property int whiteBlackMove: 0

    property int starting_piece: -1
    property int plyNumber: 0
    property int moveNumber: 0
    property int whiteMoveNumber: 0
    property int blackMoveNumber: 0
    property string currentMove: ""
    property int i: 0
    property int currentMoveNumber: 0
    property var listOfMoves: [{move: ""}]
    property alias pieces: repeaterPieces

    Image
    {
        id: img_boardTexture
        source: "images/cg_board.png"

        width: root.width
        height: root.height
    }

    Audio
    {
        id: iPod2
        source: "Sounds/move.mp3"
        autoLoad: true
    }

    Audio
    {
        id: iPod
        source: "Sounds/wrongMove.mp3"
        autoLoad: true
    }

    Repeater
    {
        id: board
        model: 64

        Rectangle
        {
            id: rect
            color: Board.getWhiteOrBlack(index)

            opacity: 0.45
            width: Board.getSquareSize()
            height: Board.getSquareSize()

            x: Board.getX(index)
            y: Board.getY(index)
        }
    }

    MouseArea
    {
        anchors.fill: parent

        onMouseXChanged:
        {
            current_piece.x = mouse.x - (current_piece.width / 2)

            if (starting_position && starting.x !== ((mouse.x - (mouse.x % Board.getSquareSize())) + Board.getBoardOffset()))
            {
                repeaterPieces.itemAt(starting_index).currentFrame = 12
                current_piece.visible = true
            }
        }

        onMouseYChanged:
        {
            current_piece.y = mouse.y - (current_piece.height / 2)

            if (starting_position && starting.y !== ((mouse.y - (mouse.y % Board.getSquareSize())) + Board.getBoardOffset()))
            {
                repeaterPieces.itemAt(starting_index).currentFrame = 12
                current_piece.visible = true
            }
        }

        onPressed:
        {
            if (starting_position == false)
            {
                starting.visible = false
                ending.visible = false

                starting_position = true
                starting_index = Board.getIndex(mouse.x - Board.getBoardOffset(), mouse.y - Board.getBoardOffset())
                starting.x = Board.getX(starting_index)
                starting.y = Board.getY(starting_index)

                // This allows us to undo a movement if not validated.
                starting_piece = repeaterPieces.itemAt(starting_index).currentFrame

                ending.visible = false

                current_piece.frame = starting_piece
            }
        }

        onReleased:
        {
            if (starting_position == true)
            {
                starting.visible = true
                ending.visible = true

                ending_index = Board.getIndex(mouse.x - Board.getBoardOffset(), mouse.y - Board.getBoardOffset())

                if (starting_index != ending_index)
                {
                    ending.x = Board.getX(ending_index)
                    ending.y = Board.getY(ending_index)

                    if (BoardLogic.getSquare(Board.getRow(starting_index), Board.getColumn(starting_index)) !== "")
                    {
                        if (gameOver || !BoardLogic.move(Board.getRow(starting_index), Board.getColumn(starting_index), Board.getRow(ending_index), Board.getColumn(ending_index)))
                        {
                            //Play wrong move sound
                            iPod2.play()
                        }
                        else
                        {
                            //Make sound on successful movement
                            iPod.play()

                            // Toggle the current player's LED if the movement was made.
                            whiteBlackMove = whiteBlackMove == 1 ? 0 : 1

                            //Increment ply number
                            plyNumber++

                            //Check whose turn it is
                            plyNumber % 2 != 0 ? whiteMoveNumber++ : blackMoveNumber++
                            plyNumber % 2 != 0 ? moveNumber = whiteMoveNumber : moveNumber = blackMoveNumber

                            //Convert y to file
                            var file = Board.getColumn(ending_index)

                            //Convert x to rank
                            var rank = Board.getRow(ending_index)

                            //Update current move
                            currentMove = moveNumber + Board.pieceToString(current_piece.frame) + Board.yToFile(file) + Board.xToRank(rank)

                            //Store current move in list
                            listOfMoves.push({move: currentMove})
                            currentMoveNumber++
                        }

                        // Update the board's pieces after a movement
                        Board.refreshBoard(repeaterPieces)
                    }

                    starting_position = false
                }

                // Set the draggable piece to invisible while not being dragged.
                current_piece.visible = false
            }
        }
    }

    // Display Pieces
    Repeater
    {
        id: repeaterPieces
        model: 64

        Rectangle
        {
            width: Board.getSquareSize()
            height: Board.getSquareSize()

            property int currentFrame: Board.setPiece(BoardLogic.getSquare(Board.getRow(index), Board.getColumn(index)))

            x: Board.getX(index)
            y: Board.getY(index)

            color: "transparent"

            CG_piece
            {
                id: piece

                frame: currentFrame
                source: "images/cg_pieces.png"
                running: false
                frameCount: 12

                anchors.fill: parent
            }
        }
    }

    // Show the start of a move by highlighting the square
    Rectangle
    {
        id: starting

        color: "transparent"
        border.color: "#FF5555"
        border.width: getSmallestOrientation() * 0.01
        opacity: 0.8

        width: Board.getSquareSize()
        height: Board.getSquareSize()
        visible: false

        x: Board.getX(50)
        y: Board.getY(50)
    }

    // Show the end of a move by highlighting the square
    Rectangle
    {
        id: ending

        color: "transparent"
        border.color: "#5555FF"
        border.width: getSmallestOrientation() * 0.01
        opacity: 0.8

        width: Board.getSquareSize()
        height: Board.getSquareSize()
        visible: false

        x: Board.getX(51)
        y: Board.getY(51)
    }

    CG_piece
    {
        id: current_piece
        visible: false
        width: Board.getSquareSize() * 2
        height: Board.getSquareSize() * 2
        source: "images/cg_pieces.png"
        running: false
        frameCount: 12

        x: starting.x
        y: starting.y
    }

    onWidthChanged:
    {
        starting.visible = false
        ending.visible = false
    }

    onHeightChanged:
    {
        starting.visible = false
        ending.visible = false
    }
}
