import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0

Item {
    id: root
    width: 400
    height: 600

    signal goBack

    ColumnLayout
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 6

        RowLayout
        {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: parent.width

            Clock
            {
                city: "Klamath Falls"
                shift: -8
            }

            ColumnLayout
            {
                spacing: 6

                Text
                {
                    id: lbl_username
                    text: "Trudodyr"

                    color: "white"
                    font.family: "Helvetica"
                    font.bold: true
                    font.pixelSize: 16
                    style: Text.Raised
                    styleColor: "black"
                }

                Text
                {
                    id: lbl_eloRating
                    text: "ELO: 2710"
                    textFormat: horizontalAlignment


                    color: "white"
                    font.family: "Helvetica"
                    font.bold: true
                    font.pixelSize: 16
                    style: Text.Raised
                    styleColor: "black"
                }
            }
        }

        Button
        {
            id: btn_oneMinuteGame
            text: "1 Minute"
            style: cgButtonStyle

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: getControlWidth()
            Layout.preferredHeight: getControlHeight()

            onClicked: root.goBack()
        }

        Button
        {
            id: btn_fiveMinuteGame
            text: "5 Minute"
            style: cgButtonStyle

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: getControlWidth()
            Layout.preferredHeight: getControlHeight()

            onClicked: root.goBack()
        }

        Button
        {
            id: btn_thirtyMinuteGame
            text: "30 Minute"
            style: cgButtonStyle

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: getControlWidth()
            Layout.preferredHeight: getControlHeight()

            onClicked: root.goBack()
        }

        RowLayout
        {
            Layout.alignment: Qt.AlignCenter

            Button
            {
                id: btn_logout
                text: "Logout"
                style: cgButtonStyle

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: getControlWidth() / 2
                Layout.preferredHeight: getControlHeight()

                onClicked: root.goBack()
            }

            Button
            {
                id: btn_settings
                text: "Settings"
                style: cgButtonStyle

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: getControlWidth() / 2
                Layout.preferredHeight: getControlHeight()

                onClicked: root.goBack()
            }
        }
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
                radius: 40
            }
        }
    }
}
