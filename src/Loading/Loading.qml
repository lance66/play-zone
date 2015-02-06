import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

// Displays circles on the screen
Item
{
    width: 400
    height: 600

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    function sizeOfCircle()
    {
        // 1/7 leaves spacing for the six circles along with the proper
        // amount of spacing needed for each circle.
        return getSmallestOrientation() * (1/7)
    }

    Row
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        // smallest orientation / 6 circles subtract
        // smallest orientation / 7 circles for the spacing
        // divide the difference of the result by smallest orientation = .0238.
        spacing: getSmallestOrientation() * .0238

        Repeater
        {
            model: 6

            Rectangle
            {
                height: sizeOfCircle()
                width: sizeOfCircle()
                radius: width * .5
                color: "#b6ee65"
                smooth: true
            }
        }
    }

    Text
    {
        text: "Gathering pieces..."

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        color: "black"
        font.family: "Helvetica"
        font.bold: true
        style: Text.Raised
        styleColor: "white"

        // Adjusts font size for scalability
        font.pixelSize: getSmallestOrientation() * 0.04
    }
}
//  End Displays 6 circles on the screen.

// ********* Below is the sample animation code i was working on I was trying to get it to animate without having to click on anything but it's not doing that************
//Item
//{
//    width: 300; height: 300

//    Rectangle {
//        id: rect
//        width: 75; height: 75
//        color: "blue"
//        opacity: 1.0

//        MouseArea
//        {
//            anchors.fill: parent
//            onClicked:
//            {
//                Animator.start()
//            }
//        }

//        PropertyAnimation {id: animateColor; target: rect; properties: "color"; to: "green"; duration: 100}

//        SpringAnimation
//        {
//            id: animateOpacity
//            target: flashingblob
//            properties:
//            from: 0.99
//            to: 1.0
//            loops: Animation.Infinite
//            easing {type: Easing.OutBack; overshoot: 500}
//       }
//    }
