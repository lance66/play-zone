import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

// Displays circles on the screen
Item
{
    width: 100
    height: 62
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    Row
    {
        anchors.horizontalCenter: parent.horizontalCenter
        //anchors.verticalCenter: parent.verticalCenter
        spacing: 10

        Repeater
        {
            model: 6

            Rectangle
            {
                height: 100
                width: 100
                radius: width * .5
                color: "#b6ee65"
                smooth: true
            }
        }
    }
//  Displays 6 circles on the screen.



}

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
