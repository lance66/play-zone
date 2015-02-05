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

    property bool starting_position: false

    Column
    {
        Repeater
        {
            model: 4

            Column
            {
                id: column

                Row
                {
                    Repeater
                    {
                        model: 8

                        Rectangle
                        {
                            width: getBackgroundHeight() / 16
                            height: getBackgroundHeight() / 16

                            color: index % 2 == 0 ? "#FFFFFF" : "#000000"

                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {

                                    if (starting_position == false)
                                    {
                                        starting.x = parent.x
                                        starting.y = column.y
                                        starting_position = true
                                    }
                                    else
                                    {
                                        ending.x = parent.x
                                        ending.y = column.y
                                        starting_position = false
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
                        model: 8

                        Rectangle
                        {
                            width: getBackgroundHeight() / 16
                            height: getBackgroundHeight() / 16

                            color: index % 2 == 0 ? "#000000" : "#FFFFFF"

                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    if (starting_position == false)
                                    {
                                        starting.x = parent.x
                                        starting.y = column.y + (getBackgroundHeight() / 16)
                                        starting_position = true
                                    }
                                    else
                                    {
                                        ending.x = parent.x
                                        ending.y = column.y + (getBackgroundHeight() / 16)
                                        starting_position = false
                                    }
                                }
                            }
                        }
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
        width: getBackgroundHeight() / 16
        height: getBackgroundHeight() / 16
    }

    Rectangle
    {
        id: ending
        color: "#5555FF"
        opacity: 0.8
        width: getBackgroundHeight() / 16
        height: getBackgroundHeight() / 16
    }
}
