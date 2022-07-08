import QtQuick
import QtQuick.Controls.Material
import QtQuick.Layouts

ApplicationWindow {
    id: _window
    width: 640
    height: 823
    visible: true
    title: qsTr("Hello World")
    Material.theme: Material.Light
    minimumWidth: 369
    maximumWidth: 1800
    minimumHeight: 480
    maximumHeight: 1080
    readonly property bool _isDesktop: (_window.width >= 1200)
    readonly property bool _isTablet: (_window.width <= 979 && _window.width >= 768)
    readonly property bool _isMobile: (_window.width <= 767 && _window.width >= 480)
    readonly property bool _isMini: (_window.width <= 479 && _window.width >= 370)
    Connections{
        target: _user
        function onUserProfileChanged(){
            _loader.sourceComponent = _lbl
        }
    }
    Component{
        id: _lbl
        Label{
            font: Typography.bold.h2
            anchors.centerIn: parent
            text: "Login user."
        }
    }
    Loader{
        id: _loader
        anchors.fill: parent
        visible: true
        active: visible
        sourceComponent: LandingPage{}
    }
}
