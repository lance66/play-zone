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
    return (current_index % 8) * getSquareSize() + getBoardOffset()
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
    return row * getSquareSize() + getBoardOffset()
}

/**************************************************************
*	  Purpose:  Refreshes the pieces on the board.
*
*     Entry:    User has entered a game.
*
*     Exit:     The board's pieces are updated.
****************************************************************/

function refreshBoard(repeaterPieces)
{
    for (var currentPiece = 0; currentPiece < repeaterPieces.count; ++currentPiece)
        repeaterPieces.itemAt(currentPiece).frame = setPiece(BoardLogic.getSquare(getRow(currentPiece), getColumn(currentPiece)))
}

/**************************************************************
*	  Purpose:  Returns the offset of the board itself.
*               This is the offset from the texture behind
*               to the board pattern.
*
*     Entry:    User has entered a game.
*
*     Exit:     The board has the offset from the top left corner
*               of the CG_board qml object that exists within
*               CG_game.
****************************************************************/

function getBoardOffset()
{
    return (img_boardTexture.width - (getSquareSize() * 8)) / 2
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
    return ((Math.floor(y / getSquareSize()) * 8) + Math.floor(x / getSquareSize())) % 64
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

function forward(moves, current)
{
    //Move current index backwards
    return ++current
}

function backward(moves, current)
{
    //Move current index backwards
    return --current
}

function current(moves, current)
{
    return moves[current].move
}

function getCurrentMove()
{
    return currentMove
}

