import QtQuick
import QtQuick.Controls

Rectangle {
    x: 100
    y: 100
    width: parent.width - 200
    height: parent.height - 200
    visible: false

    Button {
        id: closeSettings
        x: parent.width - 30
        y: parent.height - 30
        width: 30
        height: 30
        onClicked: {
            if(Qt.LeftButton){
                parent.visible = false;
            }
        }
    }

    function showSettings(){
        if(!settingsModule.visible){
            settingsModule.visible = true
        }
    }
}
