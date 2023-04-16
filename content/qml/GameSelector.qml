import QtQuick
import QtQuick.Controls

import cGameChangerListUrl
import "customModules"

Item {
    property var mainTextColor: Qt.rgba(1, 1, 1, 1)
    property int currentGameId: 0

    ListView {
        id: selectGame
        x: 20
        y: 20
        width: mainwindow.width_1 * 35 * mainwindow.baseScale
        height: 120 * mainwindow.baseScale
        spacing: 10 * mainwindow.baseScale

        clip: true
        orientation: Qt.Horizontal

        model: GameChanger {
            list: ObjcGameChangerList
        }

        delegate: Item {
            id: item
            width: 60 * mainwindow.baseScale
            height: 60 * mainwindow.baseScale
            CustomButton {
                x: 1
                y: 1
                width: 58
                height: 58
                bImage.source: "../../images/gameBackgrounds/icon_" + model.gameId + ".png"
                bDesc: "Total War " + gameName
                MouseArea {
                    id: mouseHover
                    anchors.fill: parent
                    onClicked: {
                        if(Qt.LeftButton){
                            setGame(index);
                        }
                    }
                }
            }
            Rectangle {
                id: gameBorder
                anchors.fill: parent
                color: "#00000000"
                border.width: 1
                border.color: mainwindow.rectangleBorder
            }
        }
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

        qmlModsList.visible = true;
    }
}
