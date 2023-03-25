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

    ComboBox {
        id: selectGame
        editable: false
        model: GameChanger {
            list: ObjcGameChangerList
        }

        onActivated: {
            setGame(currentIndex);
        }
        x: mainwindow.width_1 * 20 * mainwindow.baseScale
        y: 0
        width: 250 * mainwindow.baseScale
        height: 30 * mainwindow.baseScale
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
