import QtQuick
import QtQuick.Controls

import ModPacksList


Item {
    Rectangle {
        id: empty_holder_mods
        ComboBox {
            id: selectModpack
            editable: true
            model: ModpacksList {
                list: ObjModpacksContent
            }

            onActivated: loadAndRefresh(currentIndex);
            font.pixelSize: 18
            x: ((Window.width - (this.width + 450)) > 1175) ? 1175 : Window.width - (this.width + 450)
            y: 790
            width: 300
            height: 30
        }

        Button {
            id: createModpack
            x: Window.width - (this.width + 310)
            y: 790
            width: 125
            height: 30
            font.pixelSize: 18
            text: qsTr("Save Pack")
            onClicked: {
               if(Qt.LeftButton)
                   {
                       if (selectModpack.find(selectModpack.editText) === -1)
                       {
                           ObjModpacksContent.saveModlist(selectModpack.editText)
                           selectModpack.model.refreshList()
                       }
                   }
               }
        }

        Button {
            id: deleteModpack
            x: Window.width - (this.width + 310)
            y: 835
            width: 125
            height: 30
            font.pixelSize: 18
            text: qsTr("Delete Pack")
            onClicked: {
               if(Qt.LeftButton)
                   {
                       ObjModpacksContent.removeItem(selectModpack.currentIndex)
                   }
               }
        }

        Button {
            id: play
            x: Window.width - (this.width + 70)
            y: Window.height - (this.height + 80)
            width: 100
            font.pixelSize: 20
            text: qsTr("Play")
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
        modlist.refreshModlist();
    }
}
