import QtQuick
import QtQuick.Controls

import cGameChangerListUrl

Rectangle {
    x: 100
    y: 100
    width: parent.width - 200
    height: parent.height - 200
    visible: false

    property int defaultGame: 11

    Button {
        id: closeSettings
        x: parent.width - 30
        y: 0
        width: 30
        height: 30
        onClicked: {
            if(Qt.LeftButton){
                qmlTopMenu.enableLeftRightBottom();
                parent.visible = false;
            }
        }
    }

    Text {
        id: selectDefaultGameText
        x: 20
        y: 20
        text: "Select default game"
        font.pointSize: 14
    }

    ComboBox {
        id: selectDefaultGame
        editable: false
        model: GameChanger {
            list: ObjcGameChangerList
        }

        onActivated: {
            qmlGameSelector.setGame(currentIndex);
            // Add later saving as default game
        }
        x: 30 + selectDefaultGameText.implicitWidth
        y: 20
        width: 250
        height: 30
    }

    function showSettings(){
        if(!qmlSettingsModule.visible){
            qmlSettingsModule.visible = true
        }
    }
}
