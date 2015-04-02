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
    property alias startingMove: starting
    property alias endingMove: ending
    property int translation: 0
    signal clientMoved

    Connections
    {
        target: ServerConnection

        onMatchConnected:
        {
            Board.refreshBoard(repeaterPieces, translation)
        }
        onIAmBlack:
        {
            translation = 7
        }
    }

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
        property bool selectedPieceColor: false
        onMouseXChanged:
        {
            current_piece.x = mouse.x - (current_piece.width / 2)

            if (starting_position && starting.x !== ((mouse.x - (mouse.x % Board.getSquareSize())) + Board.getBoardOffset()))
            {
                repeaterPieces.itemAt(starting_index).frame= 12
                current_piece.visible = true
            }
        }

        onMouseYChanged:
        {
            current_piece.y = mouse.y - (current_piece.height / 2)

            if (starting_position && starting.y !== ((mouse.y - (mouse.y % Board.getSquareSize())) + Board.getBoardOffset()))
            {
                repeaterPieces.itemAt(starting_index).frame = 12
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

                //Our board has a texture so the board itself is offset
                //we need to account for it in our indexes.
                starting_index = Board.getIndex(mouse.x - Board.getBoardOffset(), mouse.y - Board.getBoardOffset())


                starting.x = mouse.x - Board.getX(0)
                starting.y = mouse.y - Board.getY(0)

                // starting.x = Board.getX(starting_index)
                // starting.y = Board.getY(starting_index)
                selectedPieceColor = BoardLogic.getPieceColorAt(starting.y / Board.getSquareSize(), starting.x / Board.getSquareSize())
                starting_position = ((selectedPieceColor === ServerConnection.getColor()) && (selectedPieceColor === (whiteBlackMove == 1)) )

                // This allows us to undo a movement if not validated.
                starting_piece = repeaterPieces.itemAt(starting_index).frame

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

                //Our board has a texture so the board itself is offset
                //we need to account for it in our indexes.
                ending_index = Board.getIndex(mouse.x - Board.getBoardOffset(), mouse.y - Board.getBoardOffset())

                //Ensure the piece has actually moved.
                if (starting_index != ending_index)
                {
                    ending.x = Board.getX(ending_index)
                    ending.y = Board.getY(ending_index)

                    //Ensure that the player is actually picking up a piece.
                    if (BoardLogic.getSquare(Board.getRow(starting_index), Board.getColumn(starting_index)) !== "")
                    {
                        if (gameOver || !BoardLogic.move(Board.getRow(starting_index), Board.getColumn(starting_index), Board.getRow(ending_index), Board.getColumn(ending_index)))
                                      //!BoardLogic.move(Math.abs(translation - Board.getRow(starting_index)), Math.abs(translation - Board.getColumn(starting_index)), Math.abs(translation - Board.getRow(ending_index)), Math.abs(translation - Board.getColumn(ending_index))))
                        {
                            //Play wrong move sound
                            iPod2.play()
                        }
                        else
                        {
                            //Make move on server
                            root.clientMoved()

                            // Update the board's pieces after a movement
                            ServerConnection.sendMove(Math.abs(translation - Board.getRow(starting_index)), Math.abs(translation - Board.getColumn(starting_index)), Math.abs(translation - Board.getRow(ending_index)), Math.abs(translation - Board.getColumn(ending_index)))
                            //ServerConnection.sendMove(Board.getRow(starting_index), Board.getColumn(starting_index), Board.getRow(ending_index), Board.getColumn(ending_index))

                            // TODO -- Move to game.qml
                            // Make sound on successful movement
                            iPod.play()

                            // TODO -- Move to game.qml
                            // Toggle the current player's LED if the movement was made.

                            whiteBlackMove = whiteBlackMove == 1 ? 0 : 1
                            //whiteBlackMove = whiteBlackMove == 0 ? 1 : 0

                            // TODO -- Move to game.qml
                            // Increment ply number
                            plyNumber++

                            // TODO -- Move to game.qml
                            // Check whose turn it is
                            plyNumber % 2 != 0 ? whiteMoveNumber++ : blackMoveNumber++
                            plyNumber % 2 != 0 ? moveNumber = whiteMoveNumber : moveNumber = blackMoveNumber

                            // TODO -- Move to game.qml
                            // Convert y to file
                            var file = Board.getColumn(ending_index)

                            // TODO -- Move to game.qml
                            // Convert x to rank
                            var rank = Board.getRow(ending_index)

                            // TODO -- Move to game.qml
                            // Update current move
                            currentMove = moveNumber + Board.pieceToString(current_piece.frame) + Board.yToFile(file) + Board.xToRank(rank)

                            // TODO -- Move to game.qml
                            // Store current move in list
                            listOfMoves.push({move: currentMove})
                            currentMoveNumber++
                        }

                        Board.refreshBoard(repeaterPieces, translation)
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

            //Get the piece from the business layer.

            property alias frame: piece.frame
            //property int currentFrame: Board.setPiece(BoardLogic.getSquare(Board.getRow(index), Board.getColumn(index)))

            x: Board.getX(index)
            y: Board.getY(index)

            color: "transparent"

            CG_piece
            {
                id: piece

                frame: 12

                running: false
                frameCount: 12

                anchors.fill: parent
            }
        }

        Component.onCompleted:
        {
                for (var index = 0; index < 64; ++index)
                {
                    repeaterPieces.itemAt(Board.getSquareIndex(Math.abs(translation - Board.getRow(starting_index)), Math.abs(translation - Board.getColumn(starting_index))));

                    //repeaterPieces.itemAt(Board.getSquareIndex(Board.getRow(Math.abs(translation - index)), Board.getColumn(Math.abs(translation - index)))).frame = Board.setPiece(BoardLogic.getSquare(Board.getRow(index), Board.getColumn(index)));
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

    //Hide the movement selections when the screen size is changed.
    onWidthChanged:
    {
        starting.visible = false
        ending.visible = false
    }

    //Hide the movement selections when the screen size is changed.
    onHeightChanged:
    {
        starting.visible = false
        ending.visible = false
    }
}
