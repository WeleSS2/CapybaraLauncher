import QtQuick
import QtQuick.Controls

Button {
    id: customButton
    property alias bBackground: customButtonBackground
    property alias bImage: customButtonImage
    property bool bHover: true
    property alias bText: customButtonText
    property string bDesc: ""

    property bool buttonIsHovered: false

    background: Rectangle {
        color: "transparent"
        Rectangle {
            id: customButtonBackground
            anchors.fill: parent
            color: mainwindow.rectangleColor
            border.width: 1
            border.color: mainwindow.rectangleBorder
        }
        Image {
            id: customButtonImage
            anchors.fill: parent
            visible: source !== ""
            source: ""
        }
        Rectangle {
            id: customButtonHover
            anchors.fill: parent
            enabled: parent.enabled
            color: "#2DFFFFFF"
            visible: buttonIsHovered
        }
        MouseArea {
            id: buttonHovered
            anchors.fill: parent
            enabled: parent.enabled
            hoverEnabled: true
            onEntered: {
                if(bHover){
                    buttonIsHovered = true;
                }
            }
            onExited: {
                if(bHover){
                    buttonIsHovered = false;
                }
            }
        }
    }
    indicator: Text {
        id: customButtonText
        anchors.centerIn: parent
        visible: text !== ""
        font.pixelSize: 16
        font.bold: true
        color: mainwindow.mainTextColor
        text: ""
    }
    Item {
        anchors.fill: parent
        ToolTip {
            visible: buttonIsHovered && bDesc !== ""
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
    }
}
