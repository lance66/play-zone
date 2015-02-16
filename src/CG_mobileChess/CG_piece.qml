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

    // Used for keeping the proportion of the
    // width to 1/12 of the width of the tilesheet
    // for each piece.
    onWidthChanged:
    {
        image.width = root.width * 12
    }

    // Used for adjusting the height of the tilesheet
    // to the full size of the piece height
    onHeightChanged:
    {
        image.height = root.height
    }

    Image
    {
         id: image

         // Moves the image to the correct position
         // to display the current frame.
         x: -root.width * root.frame
    }

    // Used for animation through the tilesheet if
    // we ever want to use this in the future.
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

    // Used to increment through frames
    function nextFrame()
    {
        root.frame = ++root.frame  % root.frameCount
    }
}
