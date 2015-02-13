import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0

Item
{
    //property alias radius: background.radius
    //property alias color: background.border.color

    id: root
    width: getBackgroundHeight() / 2
    height: getBackgroundHeight() / 2
    anchors.horizontalCenter: parent.horizontalCenter


    property bool starting_position: false
    property int starting_index: -1
    property int ending_index: -1

    function getSquareSize()
    {
        return getBackgroundHeight() / 18
    }

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

    function getX(current_index)
    {
        return (current_index % 8) * getSquareSize() + ((img_boardTexture.width - (getSquareSize() * 8)) / 2)
    }

    function getY(current_index)
    {
        var row = parseInt(current_index / 8)
        return row * getSquareSize() + ((img_boardTexture.width - (getSquareSize() * 8)) / 2)
    }

    function getRow(current_index)
    {
        return parseInt(current_index / 8)
    }

    function getColumn(current_index)
    {
        return (current_index % 8)
    }

    function setPiece(piece)
    {
        var frame = 0

        if (piece == "King1")
            frame = 0
        else if (piece == "Queen1")
            frame = 1
        else if (piece == "Knight1")
            frame = 2
        else if (piece == "Bishop1")
            frame = 3
        else if (piece == "Rook1")
            frame = 4
        else if (piece == "Pawn1")
            frame = 5
        else if (piece == "King0")
            frame = 6
        else if (piece == "Queen0")
            frame = 7
        else if (piece == "Knight0")
            frame = 8
        else if (piece == "Bishop0")
            frame = 9
        else if (piece == "Rook0")
            frame = 10
        else if (piece == "Pawn0")
            frame = 11

        return frame
    }

    Image
    {
        id: img_boardTexture
        source: "images/cg_board.png"

        width: getBackgroundHeight() / 2
        height: getBackgroundHeight() / 2
    }

    Repeater
    {
        id: board
        model: 64

        Rectangle
        {
            color: getWhiteOrBlack(index)

            opacity: 0.45
            width: getSquareSize()
            height: getSquareSize()

            x: getX(index)
            y: getY(index)

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    pawn.x = parent.x
                    pawn.y = parent.y

                    if (starting_position == false)
                    {
                        starting.x = parent.x
                        starting.y = parent.y
                        starting_position = true
                        starting_index = index

                        ending.visible = false
                    }
                    else
                    {
                        ending.visible = true
                        ending.x = parent.x
                        ending.y = parent.y
                        ending_index = index

                        Board.move(getRow(starting_index), getColumn(starting_index), getRow(ending_index), getColumn(ending_index))

                        starting_position = false
                    }
                }
            }
        }
    }

    // Display Pieces
    Repeater
    {
        model: 64

        Rectangle
        {
            width: getSquareSize() * 12
            height: getSquareSize()

            x: getX(index)
            y: getY(index)

            color: "transparent"

            CG_piece
            {
                frame: setPiece(Board.getSquare(getRow(index), getColumn(index)))
                width: getSquareSize()
                height: getSquareSize()
                source: "images/cg_pieces.png"
                running: false
                frameCount: 12
            }
        }
    }

    Rectangle
    {
        id: starting
        color: "transparent"
        border.color: "#FF5555"
        border.width: getSmallestOrientation() * 0.01
        opacity: 0.8
        width: getSquareSize()
        height: getSquareSize()

        x: getX(51)
        y: getY(51)
    }

    Rectangle
    {
        id: ending
        color: "transparent"
        border.color: "#5555FF"
        border.width: getSmallestOrientation() * 0.01
        opacity: 0.8
        width: getSquareSize()
        height: getSquareSize()

        x: getX(51)
        y: getY(51)
    }

    // This is going to be eliminated soon in favor of the
    // business layer controlling the movement.
    // The presentation layer will send move requests, but
    // only display from the business layer.
    Image
    {
        id: pawn
        source: "images/cg_temp_pawn.png"
        width: getSquareSize()
        height: getSquareSize()
        visible: false

        x: getX(51)
        y: getY(51)

        Behavior on x { SpringAnimation { spring: 2; damping: 0.2; mass: 0.8 } }
        Behavior on y { SpringAnimation { spring: 2; damping: 0.2; mass: 0.8 } }
    }
}
