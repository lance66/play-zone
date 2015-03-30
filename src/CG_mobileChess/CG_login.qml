/************************************************************************
* File Name: CG_login.qml
*
* Overview:
*   This QML file is the presentation layer of our login screen.
*
*   A user can either login to an existing account or register a new one.
*   The registration info is completely validated with validators for:
*       - Valid username length
*       - Valid password length, and contains 1 uppercase, 1 lowercase and
*           1 number
*       - Valid email address
*
************************************************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtMultimedia 5.0

import "CG_definitions.js" as Definitions
import "CG_login.js" as Login

Item
{
    id: root
    width: 400
    height: 600

    signal loggedIn

    Audio
    {
        id: iPod
        source: "Sounds/successfulLogin.mp3"
        autoLoad: true
        loops: 79
    }

    Column
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 6

        Image
        {
            source: "images/cg_logo_hires_app.png"
            anchors.horizontalCenter: parent.horizontalCenter
            width: Login.getLogoSize()
            height: Login.getLogoSize()
        }

        Label
        {
            id: txt_isOpen
            anchors.horizontalCenter: parent.horizontalCenter
            text: Validator.getFeedback()

            // Adjusts the font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.03
        }

        TextField
        {
            id: tf_username
            placeholderText: "Chessgames username"
            style: cgTextFieldStyle

            // For testing purposes I inputted StarWars automatically
            text: "StarWars"

            // Adjusts the font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.03

            width: Login.getControlWidth()
            height: Login.getControlHeight()

            // When the text for the username is changed validate it
            onTextChanged:
            {
                root.setUsernameValidator()
            }
        }

        TextField
        {
            id: tf_password
            placeholderText: "Chessgames password"
            style: cgTextFieldStyle
            echoMode: TextInput.Password

            // For testing purposes I inputted StarWars automatically
            text: "StarWars1"

            // Adjusts the font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.03

            width: Login.getControlWidth()
            height: Login.getControlHeight()

            // When the text for the password is changed validate it
            onTextChanged:
            {
                root.setPasswordValidator()
            }
        }

        TextField
        {
            id: tf_confirmPassword
            placeholderText: "Confirm password"
            style: cgTextFieldStyle
            echoMode: TextInput.Password
            visible: false

            // Adjusts the font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.03

            width: Login.getControlWidth()
            height: Login.getControlHeight()

            // When the text for password confirmation is changed validate it
            onTextChanged: root.setConfirmPasswordValidator()
        }

        TextField
        {
            id: tf_emailAddress
            placeholderText: "Email Address"
            style: cgTextFieldStyle
            visible: false

            // Adjusts the font size for scalability
            font.pixelSize: getSmallestOrientation() * 0.03

            width: Login.getControlWidth()
            height: Login.getControlHeight()

            // When the text for email is changed validate it
            onTextChanged: root.setEmailValidator()
        }

        Button
        {
            id: btn_login
            text: "Login"
            style: cgButtonStyle

            onClicked:
            {
                if (!User.logIn(tf_username.text, tf_password.text))
                    txt_isOpen.text = "Username or password is incorrect."
                else
                {
                    // TODO -- Remove hardcoded values and have arguments be
                    // database statements
                    // Send player info to server
                    ServerConnection.setPlayerInfo(User.getUsername(), User.getCurrentELO(), "United States")

                    // Reset these values for next login.
                    txt_isOpen.text = ""
                    tf_username.text = ""
                    tf_password.text = ""
                    tf_confirmPassword.text = ""
                    tf_emailAddress.text = ""

                    ServerConnection.connectToServer("192.168.0.104", 9556);
                    //ServerConnection.connectToServer("127.0.0.1", 9556);
                    root.loggedIn()
                    iPod.play()

                }

                tf_confirmPassword.visible = false
                tf_emailAddress.visible = false

                // If the user is logging in reset the text color
                tf_username.textColor = "#000000"
                tf_password.textColor = "#000000"
            }

            width: Login.getControlWidth()
            height: Login.getControlHeight()
        }

        Button
        {
            id: btn_register
            text: "Register"
            style: cgButtonStyle
            onClicked:
            {
                txt_isOpen.text = ""

                // If the user does not exist allow the user to create the user.
                if (!User.getUser(tf_username.text))
                {
                    if (tf_confirmPassword.visible == true)
                    {
                        // Check the validators before adding a new user.
                        if (root.setValidators())
                        {
                            if (User.addUser(tf_username.text, tf_password.text, tf_emailAddress.text))
                                txt_isOpen.text = "Successfully created user."
                        }
                    }
                    else
                    {
                        /* The first time the register button is clicked it should
                           reveal the password confirmation and email address fields.*/

                        tf_confirmPassword.visible = true
                        tf_emailAddress.visible = true
                        root.setValidators()
                    }
                }
                else
                    txt_isOpen.text = "User already exists."
            }

            width: Login.getControlWidth()
            height: Login.getControlHeight()
        }

        Component
        {
            id: cgTextFieldStyle

            TextFieldStyle
            {
                background: Rectangle {
                    color: "#FFFFFF"
                    border.color: "#448ed3"
                    smooth: true
                    radius: 100
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
                        GradientStop { position: 0.0; color: control.pressed ? Definitions.BUTTON_COLOR_ON_CLICK : Definitions.TOP_COLOR_FOR_BUTTON }//"#b6ee65" : "#76ae25" }
                        GradientStop { position: 0.5; color: control.pressed ? Definitions.BUTTON_COLOR_ON_CLICK : Definitions.BOTTOM_COLOR_FOR_BUTTON /*"#fbdb65"*/ }//"#76ae25" : "#b6ee65" }
                    }

                    border.color: "#1c375b" //"#448ed3"
                    border.width: 4
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
                    color: "#000000" //"#CCFFFF"

                    text: control.text
                }
            }
        }
    }

    /**************************************************************
    *	  Purpose:  Ensures the control fields pass all the
    *               validators.
    *
    *     Entry:    User has clicked register.
    *
    *     Exit:     Returns whether the fields are valid or not.
    ****************************************************************/

    function setValidators()
    {
        return setUsernameValidator() && setPasswordValidator() && setConfirmPasswordValidator() && setEmailValidator()
    }

    /**************************************************************
    *	  Purpose:  Ensures the username is valid when registering.
    *
    *     Entry:    User has clicked register.
    *
    *     Exit:     Displays whether the username is valid or not.
    ****************************************************************/

    function setUsernameValidator()
    {
        var valid_username = true

        if (tf_confirmPassword.visible == true)
        {
            if (Validator.checkValidUsername(tf_username.text))
            {
                tf_username.textColor = "#00AA00"
                tf_username.font.bold = false
            }
            else
            {
                valid_username = false
                tf_username.textColor = "#FF0000"
                tf_username.font.bold = true
            }
        }

        return valid_username
    }

    /**************************************************************
    *	  Purpose:  Ensures the password is valid when registering.
    *
    *     Entry:    User has clicked register.
    *
    *     Exit:     Displays whether the password is valid or not.
    ****************************************************************/

    function setPasswordValidator()
    {
        var valid_password = true

        if (tf_confirmPassword.visible == true)
        {
            if (Validator.checkValidPassword(tf_password.text))
            {
                tf_password.textColor = "#00AA00"
                tf_password.font.bold = false
            }
            else
            {
                valid_password = false
                tf_password.textColor = "#FF0000"
                tf_password.font.bold = true
            }
        }

        return valid_password
    }

    /*****************************************************************
    *	  Purpose:  Ensures the password is the same when registering.
    *
    *     Entry:    User has clicked register.
    *
    *     Exit:     Displays whether the confirm password is the same.
    *******************************************************************/

    function setConfirmPasswordValidator()
    {
        var valid_confirm_password = true

        if (tf_confirmPassword.visible == true)
        {
            if (tf_password.text == tf_confirmPassword.text)
            {
                tf_confirmPassword.textColor = "#00AA00"
                tf_confirmPassword.font.bold = false
            }
            else
            {
                valid_confirm_password = false
                tf_confirmPassword.textColor = "#FF0000"
                tf_confirmPassword.font.bold = true
            }
        }

        return valid_confirm_password
    }

    /**************************************************************
    *	  Purpose:  Ensures the email is valid when registering.
    *
    *     Entry:    User has clicked register.
    *
    *     Exit:     Displays whether the email is valid or not.
    ****************************************************************/

    function setEmailValidator()
    {
        var valid_email = true

        if (tf_confirmPassword.visible == true)
        {
            if (Validator.checkValidEmailAddress(tf_emailAddress.text))
            {
                tf_emailAddress.textColor = "#00AA00"
                tf_emailAddress.font.bold = false
            }
            else
            {
                valid_email = false
                tf_emailAddress.textColor = "#FF0000"
                tf_emailAddress.font.bold = true
            }
        }

        return valid_email
    }
}
