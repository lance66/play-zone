import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0

Item
{
    id: root
    width: getSmallestOrientation()
    height: getSmallestOrientation()

    /*property int current_piece: 0

    function addPiece()
    {
        return current_piece++
    }*/

    Column
    {
        anchors.verticalCenter: parent.verticalCenter

        Repeater
        {
            model: 8

            delegate:
                Row
                {
                    Repeater
                    {
                        model: 8

                        delegate:
                            Rectangle
                            {
                                width: getSmallestOrientation() / 8
                                height: getSmallestOrientation() / 8
                                color: "#FFFFFF"
                                border.color: "#000000"
                                border.width: 1
                            }
                    }
                }
        }
    }
}
