import QtQuick

Rectangle {
    id: customButton
    property alias source: image.source


    Image {
        id: image
        anchors.fill: parent
        source: "default.png"
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}
