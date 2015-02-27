import QtQuick 2.0

Item
{
    id: root
    property int clockTime: 60 //In seconds
    property alias running: timer.running

    onWidthChanged:
    {
        tensOfMinutes.width = root.width / 5
        onesOfMinutes.width = root.width / 5
        tensOfSeconds.width = root.width / 5
        onesOfSeconds.width = root.width / 5
        colon.width = root.width / 5
    }

    onHeightChanged:
    {
        tensOfMinutes.height = root.height
        onesOfMinutes.height = root.height
        tensOfSeconds.height = root.height
        onesOfSeconds.height = root.height
        colon.height = root.height
    }

    Row
    {
        CG_image
        {
            id: tensOfMinutes
            width: 95
            height: 172
            source: "images/cg_seven_segment.png"
            frame: parseInt((clockTime / 60) / 10)
            frameCount: 11
        }

        CG_image
        {
            id: onesOfMinutes
            width: 89
            height: 172
            source: "images/cg_seven_segment.png"
            frame: ((clockTime / 60) % 10)
            frameCount: 11
        }

        CG_image
        {
            id: colon
            width: 95
            height: 172
            source: "images/cg_seven_segment.png"
            frame: 10
            frameCount: 11
        }

        CG_image
        {
            id: tensOfSeconds
            width: 95
            height: 172
            source: "images/cg_seven_segment.png"
            frame: parseInt((clockTime % 60) / 10)
            frameCount: 11
        }

        CG_image
        {
            id: onesOfSeconds
            width: 95
            height: 172
            source: "images/cg_seven_segment.png"
            frame: ((clockTime % 60) % 10)
            frameCount: 11
        }
    }

    Timer
    {
        id: timer
        interval: 1000
        running: false
        repeat: true
        onTriggered: --clockTime
    }
}
