import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import "."

Item {
    id: root
    width: 400
    height: 600

    signal loggedIn

    Column
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 6

        Image
        {
            source: "images/cg_logo_hires_app.png"
            anchors.horizontalCenter: parent.horizontalCenter
            width: getLogoSize()
            height: getLogoSize()
        }

        Label
        {
            id: txt_isOpen
            anchors.horizontalCenter: parent.horizontalCenter
            text: Validator.getFeedback()
        }

        TextField
        {
            id: tf_username
            placeholderText: "Chessgames username"
            style: cgTextFieldStyle
            width: getControlWidth()
            height: getControlHeight()
            onTextChanged: parent.setUsernameValidator()
        }

        TextField
        {
            id: tf_password
            placeholderText: "Chessgames password"
            style: cgTextFieldStyle
            echoMode: TextInput.Password

            width: getControlWidth()
            height: getControlHeight()

            onTextChanged: parent.setPasswordValidator()
        }

        TextField
        {
            id: tf_confirmPassword
            placeholderText: "Confirm password"
            style: cgTextFieldStyle
            echoMode: TextInput.Password
            visible: false

            width: getControlWidth()
            height: getControlHeight()

            onTextChanged: parent.setConfirmPasswordValidator()
        }

        TextField
        {
            id: tf_emailAddress
            placeholderText: "Email Address"
            style: cgTextFieldStyle
            visible: false

            width: getControlWidth()
            height: getControlHeight()

            onTextChanged: parent.setEmailValidator()
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
                    txt_isOpen.text = "Successfully logged in. Hello, " + tf_username.text + "!"
                    root.loggedIn()
                }

                tf_confirmPassword.visible = false
                tf_emailAddress.visible = false

                tf_username.textColor = "#000000"
                tf_password.textColor = "#000000"
            }

            width: getControlWidth()
            height: getControlHeight()
        }

        Button
        {
            id: btn_register
            text: "Register"
            style: cgButtonStyle
            onClicked:
            {
                txt_isOpen.text = ""

                if (!User.getUser(tf_username.text))
                {
                    if (tf_confirmPassword.visible == true)
                    {
                        if (parent.setValidators())
                        {
                            if (User.addUser(tf_username.text, tf_password.text, tf_emailAddress.text))
                                txt_isOpen.text = "Successfully created user."
                        }
                    }
                    else
                    {
                        tf_confirmPassword.visible = true
                        tf_emailAddress.visible = true
                        parent.setValidators()
                    }
                }
                else
                    txt_isOpen.text = "User already exists."
            }

            width: getControlWidth()
            height: getControlHeight()

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
                    radius: 40
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

        function setValidators()
        {
            return setUsernameValidator() && setPasswordValidator() && setConfirmPasswordValidator() && setEmailValidator()
        }

        function setUsernameValidator()
        {
            var valid_username = true

            if (tf_confirmPassword.visible == true)
            {
                if (Validator.checkValidUsername(tf_username.text))
                    tf_username.textColor = "#00AA00"
                else
                {
                    valid_username = false
                    tf_username.textColor = "#FF0000"
                }
            }

            return valid_username
        }

        function setPasswordValidator()
        {
            var valid_password = true

            if (tf_confirmPassword.visible == true)
            {
                if (Validator.checkValidPassword(tf_password.text))
                    tf_password.textColor = "#00AA00"
                else
                {
                    valid_password = false
                    tf_password.textColor = "#FF0000"
                }
            }

            return valid_password
        }

        function setConfirmPasswordValidator()
        {
            var valid_confirm_password = true

            if (tf_confirmPassword.visible == true)
            {
                if (tf_password.text == tf_confirmPassword.text)
                    tf_confirmPassword.textColor = "#00AA00"
                else
                {
                    valid_confirm_password = false
                    tf_confirmPassword.textColor = "#FF0000"
                }
            }

            return valid_confirm_password
        }

        function setEmailValidator()
        {
            var valid_email = true

            if (tf_confirmPassword.visible == true)
            {
                if (Validator.checkValidEmailAddress(tf_emailAddress.text))
                    tf_emailAddress.textColor = "#00AA00"
                else
                {
                    valid_email = false
                    tf_emailAddress.textColor = "#FF0000"
                }
            }
        }
    }
}
