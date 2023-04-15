import QtQuick
import QtQuick.Controls

Rectangle {
    id: customButton
    property alias bBackground: customButtonBackground
    property alias bHover: customButtonHover
    property alias bImage: customButtonImage
    property alias bText: customButtonText
    property string bDesc: ""
    Rectangle {
        id: customButtonBackground
        anchors.fill: parent
        color: mainwindow.rectangleColor
        border.width: 1
        border.color: mainwindow.rectangleBorder
    }

    Rectangle {
        id: customButtonHover
        anchors.fill: parent
        color: "#2DFFFFFF"
        visible: buttonHovered.hovered
    }

    Image {
        id: customButtonImage
        anchors.fill: parent
        source: ""
    }

    Text {
        id: customButtonText
        anchors.centerIn: parent
        font.pixelSize: 16
        font.bold: true
        color: mainwindow.mainTextColor
        text: ""
    }
    Item {
        anchors.fill: parent
        HoverHandler {
            id: buttonHovered
            acceptedDevices: PointerDevice.Mouse
            cursorShape: Qt.PointingHandCursor
        }
        ToolTip {
            visible: buttonHovered.hovered && bDesc !== ""
            contentItem: Text {
                text: bDesc
                font.pixelSize: 15
                font.bold: true
                color: mainwindow.mainTextColor
            }
            background: Rectangle {
                color: mainwindow.rectangleColor
                border.width: 1
                border.color: mainwindow.rectangleBorder
            }
        }

        //ToolTip.visible: buttonHovered.hovered && bDesc !== ""
        //ToolTip.text: bDesc
    }
}
