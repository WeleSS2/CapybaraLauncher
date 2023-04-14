import QtQuick
import QtQuick.Controls

import cGameChangerListUrl

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
            Rectangle {
                anchors.fill: parent
                color: "transparent"
                Rectangle {
                    anchors.fill: parent
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Image {
                        x: parent.x + 1
                        y: parent.y + 1
                        width: parent.width - 2
                        height: parent.height - 2
                        source: "../images/gameBackgrounds/icon_" + model.gameId + ".png"
                        Rectangle {
                            id: lightening
                            anchors.fill: parent
                            color: "#00FFFFFF"
                        }
                    }
                }
                Rectangle {
                    id: qmlGameName
                    x: parent.x * mainwindow.baseScale
                    y: parent.y + parent.height * mainwindow.baseScale
                    width: 300 * mainwindow.baseScale
                    height: 30 * mainwindow.baseScale
                    visible: false
                    color: mainwindow.rectangleColor
                    border.color: mainwindow.rectangleBorder
                    border.width: 1
                    //Image {
                    //    anchors.fill: parent
                    //    source: "../images/icons/backgroundImage.png"
                    //}
                    Text {
                        x: 10
                        y: 3
                        width: 280 * mainwindow.baseScale
                        clip: true
                        font.bold: true
                        font.pixelSize: 16
                        color: mainTextColor
                        text: "Total War " + gameName
                    }
                }

                MouseArea {
                    id: mouseHover
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        if(Qt.LeftButton){
                            setGame(index);
                        }
                    }
                    onHoveredChanged: (mouse)=> {
                        if (containsMouse) {
                            qmlGameName.visible = true;
                            lightening.color = "#22FFFFFF"
                        } else {
                            qmlGameName.visible = false;
                            lightening.color = "#00FFFFFF"
                        }
                    }
                }
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
