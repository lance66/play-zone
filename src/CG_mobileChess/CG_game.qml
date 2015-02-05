import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0

Item
{
    id: root
    width: 400
    height: 600

    signal finished

    ColumnLayout
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.fill: parent

        RowLayout
        {
            Text
            {
                id: lbl_opponent_user
                text: "Trudodyr"

                color: "white"
                font.family: "Helvetica"
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                // Adjusts font size for scalability
                font.pixelSize: getSmallestOrientation() * 0.04
            }

            Text
            {
                id: lbl_opponent_clock
                text: "01:00"

                color: "white"
                font.family: "Helvetica"
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                // Adjusts font size for scalability
                font.pixelSize:  getSmallestOrientation() * 0.04
            }
        }

        CG_board
        {

        }

        RowLayout
        {
            Text
            {
                id: lbl_username
                text: User.getUsername()

                color: "white"
                font.family: "Helvetica"
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                // Adjusts font size for scalability
                font.pixelSize:  getSmallestOrientation() * 0.04
            }

            Text
            {
                id: lbl_clock
                text: "01:00"

                color: "white"
                font.family: "Helvetica"
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                // Adjusts font size for scalability
                font.pixelSize:  getSmallestOrientation() * 0.04
            }
        }

        Button
        {
            id: btn_settings
            text: "Settings"
            style: cgButtonStyle

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: getSmallestOrientation() * 0.9
            Layout.preferredHeight: getBackgroundHeight() * 0.125

            onClicked: root.finished()
        }

        Component
        {
            id: cgButtonStyle

            ButtonStyle
            {
                background: Rectangle {
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: control.pressed ? "#b6ee65" : "#76ae25" }
                        GradientStop { position: 0.5; color: control.pressed ? "#76ae25" : "#b6ee65" }
                    }

                    border.color: "#448ed3"
                    smooth: true
                    radius: 100
                }

                label: Text {
                    font.pixelSize: getSmallestOrientation() * 0.03

                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Helvetica"
                    color: "black"

                    text: control.text
                }
            }
        }
    }
}
