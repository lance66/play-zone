import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0

Item
{
    id: root
    width: getBackgroundHeight() / 2
    height: getBackgroundHeight() / 2
    anchors.horizontalCenter: parent.horizontalCenter

    property int current_x: 0
    property int current_y: 0

    Column
    {
        spacing: 1
        Repeater
        {
            model: 4

            Column
            {
                Row
                {
                    spacing: 1
                    Repeater
                    {
                        model: 8

                        Rectangle
                        {
                            width: root.width / 8
                            height: root.height / 8

                            color: index % 2 == 0 ? "#FFFFFF" : "#000000"
                        }
                    }
                }

                Row
                {
                    spacing: 1
                    Repeater
                    {
                        model: 8

                        Rectangle
                        {
                            width: root.width / 8
                            height: root.height / 8

                            color: index % 2 == 0 ? "#000000" : "#FFFFFF"
                        }
                    }
                }
            }
        }
    }



    Row
    {
        Repeater
        {
            model: 6

            Rectangle
            {
                radius: 100
            }
        }
    }
}
