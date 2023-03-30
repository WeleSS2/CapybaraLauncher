import QtQuick
import QtQuick.Controls

import cGameChangerListUrl

Item {
    property var mainTextColor: Qt.rgba(1, 1, 1, 1)
    property int currentGameId: 0

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
        currentGameId = selectGame.model.getCurrentGameId();

        qtGeneralBackendObj.currentGameId = selectGame.model.getCurrentGameId();
        background.source = "../images/gameBackgrounds/background_" + qtGeneralBackendObj.currentGameId + ".png"
        objModsList.refreshModlistVector();
        ObjModpacksContent.modlistAmount();
        qmlBottomGameMenu.refreshModpacksList();
        qmlModsList.refreshModlist();

        // News
        cDevNewsList.clearNewsVector();
        cDevNewsList.loadNews(selectGame.model.getCurrentGameId());
        cCommunityNewsList.clearNewsVector();
        cCommunityNewsList.loadNews(selectGame.model.getCurrentGameId());
    }
}
