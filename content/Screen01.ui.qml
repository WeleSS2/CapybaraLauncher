

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import WH3_Mod_Menager

Rectangle {
    property var mainTextColor: Qt.rgba(1, 1, 1, 1)
    Image {
        id: background
        x: 0
        y: 0
        width: Window.width
        height: Window.height
        source: "images/background.jpg"
        fillMode: Image.Stretch
    }

    Image {
        id: logo
        x: 0
        y: 0
        width: 120
        height: 80
        source: "images/capybara.png"
        fillMode: Image.Stretch
        Text {
            id: title
            x: parent.width + 90
            y: 20
            width: 812
            height: 50
            color: mainTextColor
            text: qsTr("Total War Warhammer 3 Capybara Launcher")
            font.pixelSize: 40
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            lineHeight: 1
            wrapMode: Text.NoWrap
            font.family: "Courier"
        }
    }



}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

