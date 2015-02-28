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

    /******************************************************************
      *  Purpose: Retrieves the size of the circle, to aid in the
      *           dynamically resizing process.
      *
      *    Entry: NA
      *
      *     Exit: Returns the size of the circle relative to the size
      *           of the window.
    ******************************************************************/
    function sizeOfCircle()
    {
        // 1/7 leaves spacing for the six circles along with the proper
        // amount of spacing needed for each circle.
        return getSmallestOrientation() * (1/7)
    }

    /*******************************************************************
      *  Purpose: Retrieves the time it takes for the circles to
      *           complete a revolution on the screen.
      *
      *    Entry: NA
      *
      *     Exit: Returns the duration of a revolution in milliseconds.
    *******************************************************************/
    function getDuration()
    {
        return 500
    }

    anchors.horizontalCenter: parent.horizontalCenter

    signal matched

    property alias timer: timer

    Timer
    {
        id: timer
        interval: 3000
        running: false
        onTriggered:
        {
            root.matched()
            iPod.play()
        }
    }

    Audio
    {
        id: iPod
        source: "Sounds/gameStarted.mp3"
        autoLoad: true
    }


    Row
    {
        anchors.horizontalCenter: parent.horizontalCenter

        Repeater
        {
            model: 5

            Rectangle
            {
                id: rect
                height: sizeOfCircle()
                width: sizeOfCircle()
                radius: width * .5
                smooth: true
                z: index % 2 == 0 ? -1 : 2

                gradient: Gradient
                {
                    GradientStop { position: 0.0; color: "#76ae25" }
                    GradientStop { position: 0.5; color: "#b6ee65" }
                }

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
                                getBackgroundHeight() * .75
                            else
                                getBackgroundHeight() * .25
                        }
                    }

                    NumberAnimation
                    {
                        target: rect
                        property: "y"
                        duration: getDuration()
                        to: (getBackgroundHeight() / 2) - (sizeOfCircle() / 2)
                    }

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
        font.family: "Chocolate Dealer"
        font.bold: true
        style: Text.Raised
        styleColor: "white"

        z: 1

        // Adjusts font size for scalability
        font.pixelSize: getSmallestOrientation() * 0.04
    }
}
