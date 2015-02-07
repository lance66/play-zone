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

    Image
    {
        id: img_boardTexture
        source: "images/cg_board.png"
        width: getBackgroundHeight() / 2
        height: getBackgroundHeight() / 2
    }

    Repeater
    {
        model: 64

        Rectangle
        {
            color: "transparent"

            opacity: 0.45
            width: getSquareSize()
            height: getSquareSize()

            x: getX(index)
            y: getY(index)

            ColorAnimation on color { to: getWhiteOrBlack(index); duration: 3000 }

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
                        ending.visible = false
                    }
                    else
                    {
                        ending.visible = true
                        ending.x = parent.x
                        ending.y = parent.y
                        starting_position = false
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: starting
        color: "#FF5555"
        opacity: 0.8
        width: getSquareSize()
        height: getSquareSize()

        x: getX(51)
        y: getY(51)
    }

    Rectangle
    {
        id: ending
        color: "#5555FF"
        opacity: 0.8
        width: getSquareSize()
        height: getSquareSize()

        x: getX(51)
        y: getY(51)
    }

    Image
    {
        id: pawn
        source: "images/cg_temp_pawn.png"
        width: getSquareSize()
        height: getSquareSize()

        x: getX(51)
        y: getY(51)

        Behavior on x { SpringAnimation { spring: 2; damping: 0.2; mass: 0.8 } }
        Behavior on y { SpringAnimation { spring: 2; damping: 0.2; mass: 0.8 } }
    }
}
