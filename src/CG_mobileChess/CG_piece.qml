import QtQuick 2.0

Item
{
    id: root
    clip: true

    property alias running: timer.running
    property alias source:image.source

    property alias pieceWidth: image.width
    property alias pieceHeight: image.height

    property int frame:0
    property int frameCount: 0

    onWidthChanged:
    {
        image.width = root.width * 12
    }

    onHeightChanged:
    {
        image.height = root.height
    }

    Image
    {
         id: image
         x: -root.width*root.frame
     }

    Timer
    {
        id:timer
        interval: 200
        running: false
        repeat: true

        onTriggered:
        {
            nextFrame();
        }
    }

    function nextFrame()
    {
        root.frame = ++root.frame  % root.frameCount
    }
}
