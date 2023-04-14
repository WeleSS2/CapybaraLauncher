import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../customModules"

Item {
    enabled: bottomGameMenuEnabled
    property bool showMenu: false
    property bool menuActive: false
    x: 1380
    y: 100 + mainwindow.height_1 * 72 * mainwindow.baseScale
    Canvas{
        id: modpacksOptions
        width: 35
        height: 35

        property bool clicked: false

        onPaint:{
             var context = getContext("2d");
             context.reset();
             // the triangle
             context.beginPath();
             context.moveTo(12, 24);
             context.lineTo(36, 24);
             context.lineTo(25, 12);
             context.closePath();


             // the fill color
             context.fillStyle = clicked ? "green" : "#FFCC00";
             context.fill();
        }
        MouseArea {
            width: 45
            height: 45
            x: -5
            y: -5
            hoverEnabled: true
            onHoveredChanged: (mouse)=>{
                if(containsMouse){
                    parent.clicked = true;
                    parent.requestPaint();
                    showMenu = true;
                }
                else
                {
                    parent.clicked = false;
                    parent.requestPaint();
                    showMenu = false;
                }
            }
        }
    }
    Rectangle {
        id: modsListOptions
        y: -100
        width: 320
        height: 120
        visible: menuHovered.hovered || showMenu
        color: mainwindow.rectangleColor
        border.width: 1
        border.color: mainwindow.rectangleBorder
        property int buttonsWidth: 140 * mainwindow.baseScale
        property int buttonsHeight: 30 * mainwindow.baseScale
        property int buttonsTextSize: 18 * mainwindow.baseScale
        GridLayout {
            anchors.fill: parent
            columns: 2
            rows: 2
            CustomButton {
                id: createModpack
                Layout.column: 0
                Layout.row: 0
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 140 * mainwindow.baseScale
                Layout.preferredHeight: 30 * mainwindow.baseScale
                bImage.visible: false
                bText.font.pixelSize: 18
                bText.text: qsTr("Save Modlist")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(Qt.LeftButton){
                            qmlBottomGameMenu.qSaveModlist()
                            qmlBottomGameMenu.refreshModpacksList()
                        }
                    }
                }
            }

            CustomButton {
                id: deleteModpack
                Layout.column: 0
                Layout.row: 1
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 140 * mainwindow.baseScale
                Layout.preferredHeight: 30 * mainwindow.baseScale
                bImage.visible: false
                bText.font.pixelSize: 18
                bText.text: qsTr("Delete Modlist")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(Qt.LeftButton){
                            qmlBottomGameMenu.qRemoveModpack()
                            qmlBottomGameMenu.qRemoveItem()
                        }
                    }
                }
            }
            CustomButton {
                id: importPack
                Layout.column: 1
                Layout.row: 0
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 140 * mainwindow.baseScale
                Layout.preferredHeight: 30 * mainwindow.baseScale
                bImage.visible: false
                bText.font.pixelSize: 20
                bText.text: qsTr("Import")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(Qt.LeftButton){
                            qtGeneralBackendObj.importPack();
                            objModsList.refreshModlistVector();
                            qmlModsList.refreshModlistTo0();
                        }
                    }
                }
            }
            CustomButton {
                id: exportPack
                Layout.column: 1
                Layout.row: 1
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: 140 * mainwindow.baseScale
                Layout.preferredHeight: 30 * mainwindow.baseScale
                bImage.visible: false
                bText.font.pixelSize: 20
                bText.text: qsTr("Export")
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(Qt.LeftButton){
                            qtGeneralBackendObj.exportPack();
                        }
                    }
                }
            }
        }
        Item {
            anchors.fill: parent
            HoverHandler {
                id: menuHovered
                acceptedDevices: PointerDevice.Mouse
                cursorShape: Qt.PointingHandCursor
            }
        }
        onVisibleChanged: {
            if(this.visible === true){
                menuActive = true;
            }
            else
            {
                menuActive = false;
            }
        }
    }
}
