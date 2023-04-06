import QtQuick
import QtQuick.Controls

import ModPacksList


Item {
    enabled: bottomGameMenuEnabled
    y: 100 + mainwindow.height_1 * 72 * mainwindow.baseScale
    ComboBox {
        id: selectModpack
        editable: true
        model: ModpacksList {
            list: ObjModpacksContent
        }

        onActivated: loadAndRefresh(currentIndex);
        font.pixelSize: 18
        x: 1075
        width: 300
        height: 30
    }

    Rectangle {
        id: play
        x: 1600
        y: 90
        width: 160
        height: 50
        color: mainwindow.rectangleColor
        border.width: 1
        border.color: mainwindow.rectangleBorder
        Rectangle {
            anchors.fill: parent
            color: "#2DFFFFFF"
            visible: playHovered.hovered
        }

        Text {
            anchors.centerIn: parent
            font.pixelSize: 30
            font.bold: true
            color: mainwindow.mainTextColor
            text: qsTr("Play")
        }
        Item {
            anchors.fill: parent
            HoverHandler {
                id: playHovered
                acceptedDevices: PointerDevice.Mouse
                cursorShape: Qt.PointingHandCursor
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(Qt.LeftButton)
                {
                    qtGeneralBackendObj.startGame();
                }
            }
        }
    }



    function loadAndRefresh(index) {
        ObjModpacksContent.loadModlist(index);
        var modlistName = ObjModpacksContent.getModlistName(index);
        selectModpack.editText = modlistName;

        qmlModsList.onEnable();

        qmlModsList.refreshModlistTo0();
    }
    function refreshModpacksList(){
        selectModpack.model.refreshList();
    }
    function qSaveModlist() {
        ObjModpacksContent.saveModlist(selectModpack.editText)
    }
    function qRemoveModpack() {
        qtGeneralBackendObj.removeModpack(selectModpack.currentText)
    }
    function qRemoveItem() {
        ObjModpacksContent.removeItem(selectModpack.currentIndex)
    }
}
