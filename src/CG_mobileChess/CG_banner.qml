import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0

Item
{
    id: root

    property alias countryFlag: img_flag.source
    property alias playerInfo: lbl_player.text
    property bool ledActive: false
    property alias clockRunning: cg_clock.running
    property alias result: lbl_result.text
    property alias resultVisible: lbl_result.visible

    onWidthChanged:
    {
        if (isLandscape())
        {
            gridBanner.columns = 1
            gridBanner.spacing = 0
        }
        else if (isPortrait())
        {
            gridBanner.columns = 2
            gridBanner.spacing = root.width - (img_flag.width + lbl_player.width + lbl_result.width) - (rect_LED.width + cg_clock.width)
        }
    }

    onHeightChanged:
    {
        if (isLandscape())
        {
            gridBanner.columns = 1
            gridBanner.spacing = 0
        }
        else if (isPortrait())
        {
            gridBanner.columns = 2
            gridBanner.spacing = root.width - (img_flag.width + lbl_player.width + lbl_result.width) - (rect_LED.width + cg_clock.width)
        }
    }

    Grid
    {
        id: gridBanner

        columns: 2

        spacing: root.width - (img_flag.width + lbl_player.width + lbl_result.width) - (rect_LED.width + cg_clock.width)

        width: root.width
        height: root.height

        Row
        {
            Image
            {
                id: img_flag
                width: isPortrait() ? gridBanner.height : gridBanner.height / 4
                height: isPortrait() ? gridBanner.height : gridBanner.height / 4
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
}
