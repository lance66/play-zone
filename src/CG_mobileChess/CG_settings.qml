import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtMultimedia 5.0

Item
{
    id: root
    width: 400
    height: 600

    function getSmallestOrientation()
    {
        return background.width < background.height ? background.width : background.height
    }


    // The individual control height is 1/8 of the total height.
    function getControlHeight()
    {
        return background.height / 8
    }


    // The individual control width is 100% of the smallest orientation.
    function getControlWidth()
    {
        return getSmallestOrientation() * 0.9
    }


    ColumnLayout
    {
        anchors.horizontalCenter: parent.horizontalCenter

        Text
        {
            id: lbl_settings
            text: "Settings"

            color: "white"
            font.family: "Aerial"
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            font.pixelSize: 20
        }

        RowLayout
        {
            anchors.horizontalCenter: parent.horizontalCenter

            Text
            {
                id: lbl_country
                text: "Country: "
                width: 20
                color: "white"
                font.family: "Aerial"
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                Layout.alignment: Qt.AlignCenter

                font.pixelSize: 15
            }

            ComboBox
            {
                id: cb_country
                editable: true
                currentIndex: -1
                width: 20
                validator: RegExpValidator { regExp: /^[A-Za-z]+$/ }

                Layout.alignment: Qt.AlignCenter

                model: ListModel
                {
                    id: lm_country

                    ListElement { text: ""; color: "white" }
                    ListElement { text: "USA"; color: "yellow" } //color: "yellow" /*american flag*/ }
                    ListElement { text: "England"; color: "Green" /*English flag*/ }
                    ListElement { text: "Russia"; color: "Brown" /*russian flag*/ }
                }
            }
        }

        RowLayout
        {
            anchors.horizontalCenter: parent.horizontalCenter

            Text
            {
                id: lbl_sound
                text: "Sound: "
                width: 20

                color: "white"
                font.family: "Aerial"
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                Layout.alignment: Qt.AlignCenter

                font.pixelSize: 15
            }

            ComboBox
            {
                id: cb_sound
                currentIndex: -1
                width: 20
                Layout.alignment: Qt.AlignCenter

                model: ListModel
                {
                    id: lm_sound

                    ListElement { text: "On"; color: "yellow" /*american flag*/ }
                    ListElement { text: "Off"; color: "Green" /*English flag*/ }
                }
            }
        }
    }


    RowLayout
    {
        Layout.alignment: Qt.AlignBottom && Qt.AlignCenter

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Button
        {
            id: btn_back
            text: "Back"
            //style: cgButtonStyle

            Layout.preferredWidth: getControlWidth() / 2
            Layout.preferredHeight: getControlHeight()

            //Program on click event
        }

        Button
        {
            id: btn_Save
            text: "Save"
            //style: cgButtonStyle

            Layout.preferredWidth: getControlWidth() / 2
            Layout.preferredHeight: getControlHeight()

            // Program on click event
        }
    }
}
