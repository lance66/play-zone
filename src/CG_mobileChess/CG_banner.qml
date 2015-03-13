import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0

Item
{
    id: root

    property alias playerInfo: lbl_player.text
    property bool ledActive: false
    property alias clockRunning: cg_clock.running
    property alias result: lbl_result.text
    property alias resultVisible: lbl_result.visible
    property alias flagFrame: img_flag.frame

    Row
    {
        id: rowPlayerInfo

        CG_image
        {
            id: img_flag
            width: isPortrait() ? root.height : root.height / 4
            height: isPortrait() ? root.height : root.height / 4
            source: "images/countries.png"
            frame: 0
            frameCount: 24
        }

        Text
        {
            id: lbl_player

            color: "white"
            font.family: "Helvetica"
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            anchors.verticalCenter: img_flag.verticalCenter

            // Adjusts font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.04
        }

        Text
        {
            id: lbl_result
            visible: false

            horizontalAlignment: Text.AlignRight

            color: "yellow"
            font.family: "Helvetica"
            font.bold: true
            font.pixelSize: getSmallestOrientation() * 0.1
        }
    }

    Row
    {
        id: rowLEDAndClock
        x: isLandscape() ? 0 : root.width - width
        y: isLandscape() ? rowPlayerInfo.height : (height / 2)

        Rectangle
        {
            id: rect_LED
            width: getSmallestOrientation() * 0.04
            height: getSmallestOrientation() * 0.04
            radius: (getSmallestOrientation() * 0.04) * 0.5
            color: ledActive ? "#00FF00" : "#FFFFFF"

            anchors.verticalCenter: parent.verticalCenter
        }

        CG_clock
        {
            id: cg_clock

            width: getSmallestOrientation() * 0.2
            height: (getSmallestOrientation() * 0.2) * (172/475)

            clockTime: gameTimeInMinutes * 60
            running: false

            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
