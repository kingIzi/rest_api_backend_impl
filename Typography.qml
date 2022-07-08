pragma Singleton

import QtQuick

Item {
    readonly property string _regular: _regularFont.name

    FontLoader {
        id: _regularFont
        source: "fonts/ZenKakuGothicNew-Regular.ttf"
    }
    FontLoader {
        id: _boldFont
        source: "fonts/ZenKakuGothicNew-Bold.ttf"
    }
    FontLoader {
        id: _lightFont
        source: "fonts/ZenKakuGothicNew-Light.ttf"
    }

    readonly property QtObject black: QtObject{
        readonly property font p: Qt.font({
                                              family: _regularFont.name,
                                              pixelSize: Qt.application.font.pixelSize * 1.4,
                                              letterSpacing: 2
                                          })
        readonly property font h1: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 64,
                                               letterSpacing: 2,
                                           })
        readonly property font h2: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 42,
                                               letterSpacing: 2,
                                           })
        readonly property font h3: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 32,
                                               letterSpacing: 2,
                                           })
        readonly property font h4: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 28,
                                               letterSpacing: 2,
                                           })
        readonly property font h5: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 24,
                                               letterSpacing: 2,
                                           })
        readonly property font h6: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 20,
                                               letterSpacing: 2,
                                           })
    }

    readonly property QtObject black_u: QtObject{
        readonly property font p: Qt.font({
                                              family: _regularFont.name,
                                              pixelSize: Qt.application.font.pixelSize * 1.4,
                                              letterSpacing: 2,
                                              underline: true
                                          })
        readonly property font h1: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 64,
                                               letterSpacing: 2,
                                               underline: true
                                           })
        readonly property font h3: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 32,
                                               letterSpacing: 2,
                                               underline: true
                                           })
        readonly property font h4: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 28,
                                               letterSpacing: 2,
                                               underline: true
                                           })
        readonly property font h5: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 24,
                                               letterSpacing: 2,
                                               underline: true
                                           })
        readonly property font h6: Qt.font({
                                               family: _regularFont.name,
                                               pixelSize: 20,
                                               letterSpacing: 2,
                                               underline: true
                                           })
    }

    readonly property QtObject bold: QtObject{
        readonly property font p: Qt.font({
                                              family: _boldFont.name,
                                              pixelSize: Qt.application.font.pixelSize * 1.4,
                                              letterSpacing: 2,
                                              bold: true
                                          })
        readonly property font h1: Qt.font({
                                               family: _boldFont.name,
                                               pixelSize: 64,
                                               letterSpacing: 2,
                                               bold: true
                                           })
        readonly property font h2: Qt.font({
                                               family: _boldFont.name,
                                               pixelSize: 42,
                                               letterSpacing: 2,
                                               bold: true
                                           })
        readonly property font h3: Qt.font({
                                               family: _boldFont.name,
                                               pixelSize: 32,
                                               letterSpacing: 2,
                                               bold: true
                                           })
        readonly property font h4: Qt.font({
                                               family: _boldFont.name,
                                               pixelSize: 28,
                                               letterSpacing: 2,
                                               bold: true
                                           })
        readonly property font h5: Qt.font({
                                               family: _boldFont.name,
                                               pixelSize: 24,
                                               letterSpacing: 2,
                                               bold: true
                                           })
        readonly property font h6: Qt.font({
                                               family: _boldFont.name,
                                               pixelSize: 20,
                                               letterSpacing: 2,
                                               bold: true
                                           })
    }

    readonly property QtObject light: QtObject{
        readonly property font p: Qt.font({
                                              family: _lightFont.name,
                                              pixelSize: Qt.application.font.pixelSize * 1.4,
                                              letterSpacing: 2
                                          })
        readonly property font h1: Qt.font({
                                               family: _lightFont.name,
                                               pixelSize: 64,
                                               letterSpacing: 2,
                                           })
        readonly property font h3: Qt.font({
                                               family: _lightFont.name,
                                               pixelSize: 32,
                                               letterSpacing: 2,
                                           })
        readonly property font h4: Qt.font({
                                               family: _lightFont.name,
                                               pixelSize: 28,
                                               letterSpacing: 2,
                                           })
        readonly property font h5: Qt.font({
                                               family: _lightFont.name,
                                               pixelSize: 24,
                                               letterSpacing: 2,
                                           })
        readonly property font h6: Qt.font({
                                               family: _lightFont.name,
                                               pixelSize: 20,
                                               letterSpacing: 2,
                                           })
    }

}
