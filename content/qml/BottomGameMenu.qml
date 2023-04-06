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

    Button {
        id: play
        x: 1575
        y: 90
        width: 125
        font.pixelSize: 20
        text: qsTr("Play")
        onClicked: {
            if(Qt.LeftButton)
            {
                qtGeneralBackendObj.startGame();
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
