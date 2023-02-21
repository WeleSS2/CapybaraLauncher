import QtQuick
import QtQuick.Controls

Item {
    property var mainTextColor: Qt.rgba(1, 1, 1, 1)
    property int currentGameId: 0
    Image {
        id: background
        x: 0
        y: 0
        width: Window.width
        height: Window.height
        source: "images/background" + currentGameId + ".jpg"
        fillMode: Image.Stretch
    }

    Image {
        id: logo
        x: 0
        y: 0
        width: 80
        height: 80
        source: "images/capybaraIcon.png"
        fillMode: Image.Stretch
        Text {
            id: title
            x: parent.width + 90
            y: 20
            width: 500
            height: 50
            color: mainTextColor
            text: qsTr("Total War Capybara Launcher")
            font.pixelSize: 40
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            lineHeight: 1
            wrapMode: Text.NoWrap
            font.family: "Courier"
        }
    }
    ComboBox {
        id: selectGame
        editable: false

        x: (Window.width /2) - 125
        y: 0
        width: 250
        height: 30
    }
}
