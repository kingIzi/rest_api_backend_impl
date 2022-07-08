import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

Page{
    id: _landingPage
    Material.background: Colors.primary.bgColor
    readonly property alias _regStack: _stack
    Component{
        id: _signInCompo
        Item{
            clip: true
            ScrollView{
                anchors.fill: parent
                Flickable{
                    contentHeight: _signInForm.implicitHeight
                    SignInForm{
                        id: _signInForm
                        anchors.fill: parent
                    }
                }
            }
        }
    }
    Component{
        id: _signUpCompo
        Item{
            clip: true
            ScrollView{
                anchors.fill: parent
                Flickable{
                    contentHeight: _signUpForm.implicitHeight
                    SignUpForm{
                        id: _signUpForm
                        anchors.fill: parent
                    }
                }
            }
        }
    }
    Pane{
        id: _loginRect
        anchors.centerIn: parent
        implicitWidth: 600
        implicitHeight: 480
        width: implicitWidth
        height: implicitHeight
        Material.background: Colors.neutral.neutral10
        Material.elevation: 4
        Binding{
            target: _loginRect.background
            property: "radius"
            value: 12
        }
        StackView{
            id: _stack
            anchors.fill: parent
            anchors.margins: 10
            initialItem: _signInCompo
        }
    }
}
