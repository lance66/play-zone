import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtMultimedia 5.0

Item
{
    id: root
    width: 400
    height: 600

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    signal matched

    property alias timer: timer

    function sizeOfCircle()
    {
        // 1/7 leaves spacing for the six circles along with the proper
        // amount of spacing needed for each circle.
        return getSmallestOrientation() * (1/7)
    }

    function getDuration()
    {
        return 500
    }

    Timer
    {
        id: timer
        interval: 48000
        running: false
        onTriggered: root.matched()
    }

    Row
    {
        anchors.horizontalCenter: parent.horizontalCenter
        y: (getBackgroundHeight() / 2) - (sizeOfCircle() / 2)

        Repeater
        {
            model: 6

            Rectangle
            {
                id: rect
                height: sizeOfCircle()
                width: sizeOfCircle()
                radius: width * .5
                color: "#b6ee65"
                smooth: true
                z: index % 2 == 0 ? -1 : 2

                SequentialAnimation
                {
                    running: true
                    loops: Animation.Infinite

                    NumberAnimation
                    {
                        target: rect
                        property: "y"
                        duration: getDuration()
                        to:
                        {
                            if (index % 2 == 0)
                                getBackgroundHeight() * .25
                            else
                                getBackgroundHeight() * .75
                        }
                    }


                    NumberAnimation
                    {
                        target: rect
                        property: "y"
                        duration: getDuration()
                        to: (getBackgroundHeight() / 2) - (sizeOfCircle() / 2)
                    }
                }
            }
        }
    }

    Text
    {
        text: "Finding Opponent..."

        anchors.horizontalCenter: parent.horizontalCenter
        y: (getBackgroundHeight() / 2) - (getSmallestOrientation() * 0.02)

        color: "white"
        font.family: "Calibri"
        font.bold: true
        style: Text.Raised
        styleColor: "white"

        z: 1

        // Adjusts font size for scalability
        font.pixelSize: getSmallestOrientation() * 0.04

    }
}

