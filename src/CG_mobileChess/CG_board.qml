import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0


Item
{
    id: root

    property bool starting_position: false
    property int starting_index: -1
    property int ending_index: -1
    property int whiteBlackMove: 0

    property int starting_piece: -1
    property int moveNumber: 1

    Image
    {
        id: img_boardTexture
        source: "images/cg_board.png"

        width: root.width
        height: root.height
    }

    Repeater
    {
        id: board
        model: 64

        Rectangle
        {
            id: rect
            color: root.getWhiteOrBlack(index)

            opacity: 0.45
            width: root.getSquareSize()
            height: root.getSquareSize()

            x: root.getX(index)
            y: root.getY(index)
        }
    }

    // Display Pieces
    Repeater
    {
        id: repeaterPieces
        model: 64

        Rectangle
        {
            width: root.getSquareSize() * 12
            height: root.getSquareSize()

            property int currentFrame: root.setPiece(Board.getSquare(root.getRow(index), root.getColumn(index)))

            x: root.getX(index)
            y: root.getY(index)

            color: "transparent"

            CG_piece
            {
                id: piece
                frame: currentFrame
                width: root.getSquareSize()
                height: root.getSquareSize()
                source: "images/cg_pieces.png"
                running: false
                frameCount: 12
            }

            MouseArea
            {
                anchors.fill: parent

                /*onClicked:
                {
                    if (starting_position == false)
                    {
                        starting.visible = false
                        ending.visible = false

                        starting.x = parent.x
                        starting.y = parent.y
                        starting_position = true
                        starting_index = index

                        // This allows us to undo a movement if not validated.
                        starting_piece = root.setPiece(Board.getSquare(root.getRow(starting_index), root.getColumn(starting_index)))

                        // Temporarily picks up the piece by removing it.
                        repeaterPieces.itemAt(starting_index).currentFrame = 12

                        ending.visible = false
                    }
                    else
                    {
                        starting.visible = true
                        ending.visible = true

                        ending.x = parent.x
                        ending.y = parent.y
                        ending_index = index

                        piece:
                        {

                            if (Board.getSquare(root.getRow(starting_index), root.getColumn(starting_index)) !== "")
                            {
                                if (!Board.move(root.getRow(starting_index), root.getColumn(starting_index), root.getRow(ending_index), root.getColumn(ending_index)))
                                {
                                    // If the movement wasn't made then reset the starting piece.
                                    repeaterPieces.itemAt(starting_index).currentFrame = starting_piece
                                }
                                else
                                {
                                    // Toggle the current player's LED if the movement was made.
                                    whiteBlackMove = whiteBlackMove == 1 ? 0 : 1
                                }
                            }
                            else
                                piece
                        }

                        // Update the destination of the piece movement.
                        repeaterPieces.itemAt(ending_index).currentFrame = setPiece(Board.getSquare(root.getRow(ending_index), root.getColumn(ending_index)))

                        starting_position = false
                    }
                }*/

                onPressed:
                {
                    if (starting_position == false)
                    {
                        starting.visible = false
                        ending.visible = false

                        starting.x = parent.x
                        starting.y = parent.y
                        starting_position = true
                        starting_index = index

                        // This allows us to undo a movement if not validated.
                        starting_piece = root.setPiece(Board.getSquare(root.getRow(starting_index), root.getColumn(starting_index)))

                        // Temporarily picks up the piece by removing it.
                        repeaterPieces.itemAt(starting_index).currentFrame = 12

                        ending.visible = false

                        current_piece.frame = starting_piece
                        current_piece.visible = true
                        current_piece.x = starting.x
                        current_piece.y = starting.y
                    }
                }

                onReleased:
                {
                    if (starting_position == true)
                    {
                        starting.visible = true
                        ending.visible = true

                        ending_index = getIndex(parent.x + mouse.x, parent.y + mouse.y)
                        ending.x = getX(ending_index)
                        ending.y = getY(ending_index)

                        //Get move number
                        moveNumber++

                        //Convert y to file
                        var file = root.getColumn(ending_index)

                        //Convert x to rank
                        var rank = root.getRow(ending_index)

                        //Convert current_piece to piece

                        setCurrentMove(moveNumber + pieceToString(current_piece.frame) + yToFile(file) + xToRank(rank))

                        piece:
                        {
                            if (Board.getSquare(root.getRow(starting_index), root.getColumn(starting_index)) !== "")
                            {
                                if (!Board.move(root.getRow(starting_index), root.getColumn(starting_index), root.getRow(ending_index), root.getColumn(ending_index)))
                                {
                                    // If the movement wasn't made then reset the starting piece.
                                    repeaterPieces.itemAt(starting_index).currentFrame = starting_piece
                                }
                                else
                                {
                                    // Toggle the current player's LED if the movement was made.
                                    whiteBlackMove = whiteBlackMove == 1 ? 0 : 1
                                }
                            }
                            else
                                piece
                        }

                        // Update the destination of the piece movement.
                        repeaterPieces.itemAt(ending_index).currentFrame = setPiece(Board.getSquare(root.getRow(ending_index), root.getColumn(ending_index)))

                        starting_position = false

                        current_piece.visible = false
                    }
                }

                drag
                {
                    target: current_piece
                    axis: Drag.XandYAxis
                }
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

        width: root.getSquareSize()
        height: root.getSquareSize()
        visible: false

        x: getX(50)
        y: getY(50)
    }

    // Show the end of a move by highlighting the square
    Rectangle
    {
        id: ending

        color: "transparent"
        border.color: "#5555FF"
        border.width: getSmallestOrientation() * 0.01
        opacity: 0.8

        width: root.getSquareSize()
        height: root.getSquareSize()
        visible: false

        x: getX(51)
        y: getY(51)
    }

    CG_piece
    {
        id: current_piece
        visible: false
        width: root.getSquareSize()
        height: root.getSquareSize()
        source: "images/cg_pieces.png"
        running: false
        frameCount: 12

        x: starting.x
        y: starting.y
    }

    /**************************************************************
    *	  Purpose:  Returns the size of each square on the board.
    *
    *     Entry:    User has entered a game.
    *
    *     Exit:     Displays the square with the given size of 1/18
    *               of the background height.
    ****************************************************************/

    function getSquareSize()
    {
        return root.width / 9
    }

    /**************************************************************
    *	  Purpose:  Returns whether the square is white or black.
    *               Used for creating the checker pattern.
    *
    *     Entry:    User has entered a game.
    *
    *     Exit:     Displays the square with the correct color.
    ****************************************************************/

    function getWhiteOrBlack(current_index)
    {
        var row = parseInt(current_index / 8)

        if (row % 2 == 0)
        {
            if (current_index % 2)
                return "#000000"
            else
                return "#FFFFFF"
        }
        else
        {
            if (current_index % 2)
                return "#FFFFFF"
            else
                return "#000000"
        }
    }

    /**************************************************************
    *	  Purpose:  Returns the x coordinate of the passed index.
    *
    *     Entry:    User has entered a game.
    *
    *     Exit:     The x coordinate is determined for the passed
    *               index.
    ****************************************************************/

    function getX(current_index)
    {
        return (current_index % 8) * getSquareSize() + ((img_boardTexture.width - (getSquareSize() * 8)) / 2)
    }

    /**************************************************************
    *	  Purpose:  Returns the y coordinate of the passed index.
    *
    *     Entry:    User has entered a game.
    *
    *     Exit:     The y coordinate is determined for the passed
    *               index.
    ****************************************************************/

    function getY(current_index)
    {
        var row = parseInt(current_index / 8)
        return row * getSquareSize() + ((img_boardTexture.width - (getSquareSize() * 8)) / 2)
    }

    /**************************************************************
    *	  Purpose:  Returns the index of a pair of coordinates
    *
    *     Entry:    User has entered a game.
    *
    *     Exit:     The index is determined based on the passed
    *               coordinates.
    ****************************************************************/

    function getIndex(x, y)
    {
        return (parseInt(y / getSquareSize()) * 8) + parseInt(x / getSquareSize())
    }

    /**************************************************************
    *	  Purpose:  Returns the row of the passed index.
    *
    *     Entry:    User has entered a game.
    *
    *     Exit:     The row is determined for the passed index.
    ****************************************************************/

    function getRow(current_index)
    {
        return parseInt(current_index / 8)
    }

    /**************************************************************
    *	  Purpose:  Returns the column of the passed index.
    *
    *     Entry:    User has entered a game.
    *
    *     Exit:     The column is determined for the passed index.
    ****************************************************************/

    function getColumn(current_index)
    {
        return (current_index % 8)
    }

    /**************************************************************
    *	  Purpose:  Returns the correct frame for the pieces
    *               tilesheet based on an integer value.
    *
    *     Entry:    User has moved a piece.
    *
    *     Exit:     The piece is set to the correct frame of the
    *               tilesheet.
    ****************************************************************/

    function setPiece(piece)
    {
        var frame = 0

        if (piece === "King1")
            frame = 0
        else if (piece === "Queen1")
            frame = 1
        else if (piece === "Knight1")
            frame = 2
        else if (piece === "Bishop1")
            frame = 3
        else if (piece === "Rook1")
            frame = 4
        else if (piece === "Pawn1")
            frame = 5
        else if (piece === "King0")
            frame = 6
        else if (piece === "Queen0")
            frame = 7
        else if (piece === "Knight0")
            frame = 8
        else if (piece === "Bishop0")
            frame = 9
        else if (piece === "Rook0")
            frame = 10
        else if (piece === "Pawn0")
            frame = 11
        else
            frame = 12

        return frame
    }

    function getMoveNumber()
    {
        return moveNumber
    }

    function pieceToString(frame)
    {
        switch(frame)
        {
        case 0:
            return "...K"
        case 1:
            return "...Q"
        case 2:
            return "...N"
        case 3:
            return "...B"
        case 4:
            return "...R"
        case 5:
            return "..."
        case 6:
            return ". K"
        case 7:
            return ". Q"
        case 8:
            return ". N"
        case 9:
            return ". B"
        case 10:
            return ". R"
        case 11:
            return ". "
        default:
            return ""
        }
    }

    function yToFile(index)
    {
        switch(index)
        {
        case 0:
            return "a"
        case 1:
            return "b"
        case 2:
            return "c"
        case 3:
            return "d"
        case 4:
            return "e"
        case 5:
            return "f"
        case 6:
            return "g"
        case 7:
            return "h"
        default:
            return ""
        }
    }

    function xToRank(index)
    {
        switch(index)
        {
        case 0:
            return 8
        case 1:
            return 7
        case 2:
            return 6
        case 3:
            return 5
        case 4:
            return 4
        case 5:
            return 3
        case 6:
            return 2
        case 7:
            return 1
        default:
            return ""
        }
    }
}
