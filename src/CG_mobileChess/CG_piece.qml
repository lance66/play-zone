import QtQuick 2.0

Item
{
    id: root
    width: getBackgroundHeight() / 16
    height: getBackgroundHeight() / 16
    anchors.horizontalCenter: parent.horizontalCenter

    Image
    {
        source: ""
        width: root.width
        height: root.height
    }
}
