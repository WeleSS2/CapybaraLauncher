import QtQuick
import QtQuick.Controls

import ModPacksList
import "../qml/customModules"


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

    CustomButton {
        id: playNew
        x: 1600
        y: 90
        width: 160
        height: 50
        bImage.visible: false
        bText.font.pixelSize: 30 * mainwindow.baseScale
        bText.text: qsTr("Play")
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
