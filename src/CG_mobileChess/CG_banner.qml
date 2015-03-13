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

        //Country flag is displayed
        CG_image
        {
            id: img_flag
            width: getCountryFlagSize()
            height: getCountryFlagSize()
            source: "images/countries.png"
            frame: 0

            //This is the number of country flags available
            //on the tilesheet.
            frameCount: 24
        }

        //Player Info (Username, ELO) is displayed
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
            font.pixelSize: getPlayerInfoFontSize()
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

            //If the led should be active then light it
            //with a green color, or if it's not set it
            //to white.
            color: ledActive ? "#00FF00" : "#FFFFFF"

            anchors.verticalCenter: parent.verticalCenter
        }

        CG_clock
        {
            id: cg_clock
            width: getSmallestOrientation() * 0.2
            height: (getSmallestOrientation() * 0.2) * (172/475)

            //Convert the game time to seconds and pass it.
            clockTime: gameTimeInMinutes * 60
            running: false

            anchors.verticalCenter: parent.verticalCenter
        }
    }

    //Result of the game (0, 1) is displayed
    Text
    {
        id: lbl_result
        visible: false

        color: "yellow"
        opacity: 0.5
        font.family: "Helvetica"
        font.bold: true
        font.pixelSize: getResultFontSize()

        anchors.centerIn: parent
    }

    //If the device or window is in "portrait orientation"
    //then return the full height of the banner so that the
    //image which has equal width and height can fill the
    //size. Or, if in landscape it'll return 1/4 of the
    //size.
    function getCountryFlagSize()
    {
        return isPortrait() ? root.height : root.height / 4
    }

    //This returns 4% of the smallest orientation
    //to be used as a font pixel size.
    //Default size is 400x600 for the application
    //so 400 < 600 => 400 * 0.04 = 16px font size.
    function getPlayerInfoFontSize()
    {
        return getSmallestOrientation() * 0.04
    }

    //This returns 10% of the smallest orientation
    //to be used as a font pixel size for the
    //result of the game.
    function getResultFontSize()
    {
        return root.height
    }
}
