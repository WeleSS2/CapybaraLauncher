import QtQuick
import QtQuick.Controls

import cGameChangerListUrl

Item {
    property var mainTextColor: Qt.rgba(1, 1, 1, 1)

    Image {
        id: background
        x: 0
        y: 0
        width: Window.width
        height: Window.height
        source: "../images/gameBackgrounds/background_" + qtGeneralBackendObj.currentGameId + ".png"
        fillMode: Image.Stretch
    }

    Image {
        id: logo
        x: 0
        y: 0
        width: 80
        height: 80
        source: "../images/icons/capybaraIcon.png"
        fillMode: Image.Stretch
        Text {
            id: title
            x: parent.width + 90
            y: 20
            width: 500
            height: 50
            color: mainTextColor
            text: qsTr("Total War Capybara Launcher")
            font.pixelSize: 40
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            lineHeight: 1
            wrapMode: Text.NoWrap
            font.family: "Courier"
        }
    }

    ComboBox {
        id: selectGame
        editable: false
        model: GameChanger {
            list: ObjcGameChangerList
        }

        onActivated: {
            setGame(currentIndex);
        }
        x: (Window.width /2) - 125
        y: 0
        width: 250
        height: 30
    }

    function setGame(index){
        selectGame.model.setCurrentGame(index);
        qtGeneralBackendObj.currentGameId = selectGame.model.getCurrentGameId();
        background.source = "../images/gameBackgrounds/background_" + qtGeneralBackendObj.currentGameId + ".png"
        objModsList.refreshModlistVector();
        ObjModpacksContent.modlistAmount();
        qmlBottomGameMenu.refreshModpacksList();
        qmlModsList.refreshModlist();
    }
}
