import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import TaskListUrl

Item {
    property bool working: false
    property bool isEmpty: true
    property bool menuOn: false

    Connections {
        target: cppTaskList
        function onPostItemAppened(){
            refreshTaskList();
            if(cppTaskList.getListSize() > 0)
            {
                working = true;
            }
        }
    }

    Connections {
        target: cppTaskList
        function onPostItemRemoved(){
            refreshTaskList();
            qmlModsList.refreshModlist();
            if(cppTaskList.getListSize() === 0){
                working = false;
            }
        }
    }

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

        ListView {
            id: taskList
            spacing: 25
            clip: true
            anchors.fill: parent
            model: MyTaskList {
                list: cppTaskList
            }

            delegate: Item {
                x: 5
                y: 5
                Text {
                    font.pixelSize: 15
                    color: mainTextColor
                    text: model.taskDescription
                }
            }
        }

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

    function refreshTaskList(){
        console.log("Refresh called");
        taskList.model.refreshList();
    }
}
