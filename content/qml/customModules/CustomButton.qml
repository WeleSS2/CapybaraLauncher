import QtQuick

Rectangle {
    id: customButton
    property alias bText: buttomText.text

    color: mainwindow.rectangleColor
    border.width: 1
    border.color: mainwindow.rectangleBorder
    Rectangle {
        anchors.fill: parent
        color: "#2DFFFFFF"
        visible: settingsHovered.hovered
    }

    Text {
        id: buttomText
        anchors.centerIn: parent
        font.pixelSize: 20 * mainwindow.baseScale
        font.bold: true
        color: mainwindow.mainTextColor
        text: bText
    }
    Item {
        anchors.fill: parent
        HoverHandler {
            id: settingsHovered
            acceptedDevices: PointerDevice.Mouse
            cursorShape: Qt.PointingHandCursor
        }
    }
}
