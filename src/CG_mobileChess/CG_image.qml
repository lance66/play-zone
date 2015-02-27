import QtQuick 2.0

Item
{
    id: root
    clip: true

    property alias source:image.source

    property int frame:0
    property int frameCount: 0

    // Used for keeping the proportion of the
    // width to 1/11 of the width of the tilesheet
    // for each piece.
    onWidthChanged:
    {
        image.width = root.width * 11
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
}
