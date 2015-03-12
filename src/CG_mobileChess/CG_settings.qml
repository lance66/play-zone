import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.0
import QtMultimedia 5.0
import "CG_definitions.js" as Definitions

Item
{
    id: root
    width: 400
    height: 600

    signal goBack

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
            font.family: customFont.name
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            font.pixelSize: getControlWidth() * 0.15
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
                font.family: customFont.name
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                Layout.alignment: Qt.AlignCenter

                font.pixelSize: getControlWidth() * 0.1
            }

            ComboBox
            {
                id: cb_country
                editable: true
                currentIndex: 0
                width: getControlWidth()
                height: getControlHeight()

                validator: RegExpValidator { regExp: /^[A-Za-z]+$/ }

                Layout.alignment: Qt.AlignCenter

                model: ListModel
                {
                    id: lm_country

                    ListElement { text: "Select a country"; /*color: ""*/ }
                    ListElement { text: "Austria" /*; color: "Austria_Flag" */}
                    ListElement { text: "Azerbaijan" /*; color: "Azerbaijan_Flag" */}
                    ListElement { text: "Belarus" /*; color: "Belarus_Flag" */}
                    ListElement { text: "Bulgaria" /*; color: "Bulgaria_Flag" */}
                    ListElement { text: "Croatia" /*; color: "Croatia_Flag" */}
                    ListElement { text: "Czech Republic" /*; color: "Czech_Republic_Flag" */}
                    ListElement { text: "Denmark" /*; color: "Denmark_Flag" */}
                    ListElement { text: "France" /*; color: "France_Flag" */}
                    ListElement { text: "Germany" /*; color: "Germany_Flag" */}
                    ListElement { text: "Greece" /*; color: "Greece_Flag" */}
                    ListElement { text: "Italy" /*; color: "Italy_Flag" */}
                    ListElement { text: "Kazakstan" /*; color: "Kazakstan_Flag" */}
                    ListElement { text: "Luxembourg" /*; color: "Luxembourg_Flag" */}
                    ListElement { text: "Poland" /*; color: "Poland_Flag" */}
                    ListElement { text: "Portugal" /*; color: "Portugal_Flag" */}
                    ListElement { text: "Romania" /*; color: "Romania_Flag" */}
                    ListElement { text: "Russia" /*; color: "Russia_Flag" */}
                    ListElement { text: "Spain" /*; color: "Spain_Flag" */}
                    ListElement { text: "Sweden" /*; color: "Sweden_Flag" */}
                    ListElement { text: "Switzerland" /*; color: "Switzerland_Flag" */}
                    ListElement { text: "Turkey" /*; color: "Turkey_Flag" */}
                    ListElement { text: "Ukraine" /*; color: "Ukraine" */}
                    ListElement { text: "United Kingdom" /*; color: "United_Kingdom_Flag" */}
                    ListElement { text: "United States" /*; color: "United_States_Flag" */}
                }
            }
        }

        RowLayout
        {
            anchors.horizontalCenter: parent.horizontalCenter

            Text
            {
                id: lbl_sound
                text: "   Sound: "
                width: 20

                color: "white"
                font.family: customFont.name
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                Layout.alignment: Qt.AlignCenter

                font.pixelSize: getControlWidth() * 0.1
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
            style: cgButtonStyle

            Layout.preferredWidth: getControlWidth() / 2
            Layout.preferredHeight: getControlHeight()

            onClicked: root.goBack()
        }

        Button
        {
            id: btn_Save
            text: "Save"
            style: cgButtonStyle

            Layout.preferredWidth: getControlWidth() / 2
            Layout.preferredHeight: getControlHeight()

            onClicked: root.goBack()
        }
    }

    Component
    {
        id: cgButtonStyle

        ButtonStyle
        {
            background: Rectangle
            {
                gradient: Gradient
                {
                    GradientStop { position: 0.0; color: control.pressed ? Definitions.BUTTON_COLOR_ON_CLICK : Definitions.TOP_COLOR_FOR_BUTTON }
                    GradientStop { position: 0.5; color: control.pressed ? Definitions.BUTTON_COLOR_ON_CLICK : Definitions.BOTTOM_COLOR_FOR_BUTTON }
                }

                border.color: "#448ed3"
                smooth: true
                radius: 100
            }

            label: Text
            {
                font.pixelSize: getSmallestOrientation() * 0.1

                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: customFont.name
                color: "black"

                text: control.text
            }
        }
    }
}
