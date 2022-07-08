import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

ColumnLayout{
    id: _col
    Item{
        Layout.fillWidth: true
        Layout.preferredHeight: _col1.implicitHeight
        ColumnLayout{
            id: _col1
            anchors.fill: parent
            anchors.margins: 20
            spacing: 4
            Label{
                id: _welcomeMsg
                text: "Please, Sign In"
                Layout.fillWidth: true
                wrapMode: "WordWrap"
                font: Typography.bold.h2
                Material.foreground: Colors.neutral.neutral100
                Component.onCompleted: font.capitalization = Font.Capitalize
                Layout.bottomMargin: 10
            }
            TextField{
                id: _email
                Layout.fillWidth: true
                placeholderText: "Enter Email"
                font: Typography.black.p
                Material.accent: Colors.primary.focus
            }
            TextField{
                id: _password
                Layout.fillWidth: true
                placeholderText: "Enter Password"
                echoMode: _check.checked ? "Normal" : "Password"
                font: Typography.black.p
                Material.accent: Colors.primary.focus
            }
            Label{
                id: _errorMsg
                text: _user.signInErrorMsg
                Layout.alignment: Qt.AlignHCenter
                horizontalAlignment: "AlignHCenter"
                font: Typography.black.p
                Material.foreground: Colors.danger.main
                visible: text.length > 0
                Component.onCompleted: font.capitalization = Font.Capitalize
            }
            CheckBox{
                id: _check
                Layout.fillWidth: true
                text: "Show Password"
                font: Typography.black.p
                Material.accent: Colors.primary.main
            }
            Label{
                id: _forgotPassword
                text: "Forgot Your Password?"
                font: _forgotPasswordHover.hovered ? Typography.black_u.p : Typography.black.p
                Layout.fillWidth: true
                Material.foreground: Colors.neutral.neutral100
                HoverHandler{
                    id: _forgotPasswordHover
                    cursorShape: "PointingHandCursor"
                    enabled: true
                }
            }
            Button{
                id: _signUpBtn
                padding: 10
                text: "Sign In"
                font: Typography.bold.h4
                Material.background: Colors.primary.main
                Layout.fillWidth: true
                Material.foreground: "#fff"
                HoverHandler{
                    id: _signUpButnHover
                    cursorShape: "PointingHandCursor"
                    enabled: true
                }
                onClicked: {
                    _user.signInUser(_email.text,_password.text)
                }
            }
            Flow{
                Layout.fillWidth: true
                spacing: 2
                Label{
                    text: "Not Registered?"
                    font: Typography.black.p
                    Layout.fillWidth: true
                    Material.foreground: Colors.neutral.neutral100
                }
                Label{
                    id: _signUpLink
                    text: "Click here"
                    font: Typography.black.p
                    Layout.fillWidth: true
                    Material.foreground: _signUpLinkHover.hovered ? Colors.primary.hover : Colors.neutral.neutral100
                    HoverHandler{
                        id: _signUpLinkHover
                        enabled: true
                    }
                    MouseArea{
                        cursorShape: "PointingHandCursor"
                        anchors.fill: parent
                        onClicked: {
                            _regStack.push(_signUpCompo)
                        }
                    }
                }
            }
        }
    }
}
