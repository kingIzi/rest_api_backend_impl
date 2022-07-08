import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

ColumnLayout{
    id: _col2
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
                text: "Please Register"
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
                text: _user.signUpErrorMsg
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
            Button{
                id: _signUpBtn
                padding: 10
                text: "Register"
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
                    _user.signUpUser(_email.text,_password.text)
                }
            }
            Flow{
                Layout.fillWidth: true
                spacing: 8
                Label{
                    text: "Already Registered?"
                    font: Typography.black.p
                    Layout.fillWidth: true
                    Material.foreground: Colors.neutral.neutral100
                }
                Label{
                    id: _signUpLink
                    text: "Login"
                    font: Typography.black.p
                    Layout.fillWidth: true
                    Material.foreground: _signUpLinkHover.hovered ? Colors.primary.hover : Colors.neutral.neutral100
                    HoverHandler{
                        id: _signUpLinkHover
                        enabled: true
                    }
                    MouseArea{
                        anchors.fill: parent
                        cursorShape: "PointingHandCursor"
                        onClicked: _regStack.pop()
                    }
                }
            }
        }
    }
}
