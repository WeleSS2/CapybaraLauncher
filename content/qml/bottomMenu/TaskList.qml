import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    property bool working: false
    property bool isEmpty: true
    property bool menuOn: false

    Rectangle
    {
        id: taskButton
        x: mainwindow.width - 40
        y: mainwindow.height - 40
        width: 40
        height: 40
        color: "transparent"
        AnimatedImage {
            id: taskButtonAnimation
            anchors.fill: parent
            source: "../../images/icons/refreshWork.gif"
            fillMode: AnimatedImage.PreserveAspectFit
            playing: working
        }

        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            onHoveredChanged: (mouse)=> {
                if(!menuOn)
                {
                    menuOn = true;
                }
            }
        }
    }

    Rectangle {
        id: taskMenu
        visible: menuOn
        x: mainwindow.width - mainwindow.width_1 * 15
        y: mainwindow.height - mainwindow.height_1 * 30
        width: mainwindow.width_1 * 15
        height: mainwindow.height_1 * 30
        color: mainwindow.rectangleColor
        border.color: mainwindow.rectangleBorder
        border.width: 1

        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            onHoveredChanged: (mouse)=> {
                if(menuOn)
                {
                    menuOn = false;
                }
            }
        }
    }
}
