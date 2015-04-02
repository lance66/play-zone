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
//    property alias countryFlag: cb_country.currentIndex
//    property alias dataModel: cb_country.model
    property int countryFlag: 0
    signal settingsChanged

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

            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            font.family: customFont.name
            font.bold: true
            style: Text.Raised
            styleColor: "black"

            font.pixelSize: getControlWidth() * 0.15
        }

        RowLayout
        {
            id: row_country
            anchors.horizontalCenter: parent.horizontalCenter

            Text
            {
                id: lbl_country
                text: "Country:"
                width: 20
                color: "white"
                font.family: customFont.name
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                //Layout.alignment: Qt.AlignCenter

                font.pixelSize: getControlWidth() * 0.1
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

                    ListElement { text: "" }
                    ListElement { text: "United States"  }
                    ListElement { text: "Austria"        }
                    ListElement { text: "Azerbaijan"     }
                    ListElement { text: "Belarus"        }
                    ListElement { text: "Bulgaria"       }
                    ListElement { text: "Croatia"        }
                    ListElement { text: "Czech Republic" }
                    ListElement { text: "Denmark"        }
                    ListElement { text: "France"         }
                    ListElement { text: "Germany"        }
                    ListElement { text: "Greece"         }
                    ListElement { text: "Italy"          }
                    ListElement { text: "Kazakstan"      }
                    ListElement { text: "Luxembourg"     }
                    ListElement { text: "Poland"         }
                    ListElement { text: "Portugal"       }
                    ListElement { text: "Romania"        }
                    ListElement { text: "Russia"         }
                    ListElement { text: "Spain"          }
                    ListElement { text: "Sweden"         }
                    ListElement { text: "Switzerland"    }
                    ListElement { text: "Turkey"         }
                    ListElement { text: "Ukraine"        }
                    ListElement { text: "United Kingdom" }
                }
            }
        }

        RowLayout
        {
            anchors.right: row_country.right

            Text
            {
                id: lbl_sound
                text: "Sound:"
                width: 20

                color: "white"
                font.family: customFont.name
                font.bold: true
                style: Text.Raised
                styleColor: "black"

                //Layout.alignment: Qt.AlignCenter
                //anchors.right: lbl_country.right

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

            onClicked:
            {
//                User.

                root.countryFlag = cb_country.currentIndex - 1
                root.settingsChanged()
            }
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
