import QtQuick
import QtQuick.Layouts

import cNews

Item {
    x: 1050
    y: 100
    id: right_panel
    enabled : rightPanelEnabled

    Connections {
        target: cDevNewsList
        function onNewsLoaded() {
             devRefreshNewsList();
         }
    }
    Connections {
        target: cCommunityNewsList
        function onNewsLoaded() {
            communityRefreshNewsList();
        }
    }

    ListView {
        id: developerCANews
        width: Window.width - 1080
        height: mainwindow.height_1 * 35 * mainwindow.baseScale
         spacing: 10 * mainwindow.baseScale
        clip: true
        flickableDirection: Flickable.HorizontalFlick
        orientation: Qt.Horizontal
        model: News {
            list: cDevNewsList
        }

        delegate: Item {
            width: mainwindow.width_1 * 15 * mainwindow.baseScale
            height: mainwindow.height_1 * 35 * mainwindow.baseScale
            Row {
                id: developerCANews_row
                spacing: 20
                Rectangle{
                    id: developerCANews_rectangle
                    width: mainwindow.width_1 * 15 * mainwindow.baseScale
                    height: mainwindow.height_1 * 35 * mainwindow.baseScale
                    color: "transparent"
                    Rectangle {
                        id: isHovered
                        anchors.fill: parent
                        visible: false
                        color: mainwindow.rectangleColor
                        border.color: mainwindow.rectangleBorder
                        border.width: 1
                    }
                    ColumnLayout {
                        Rectangle {
                            Layout.topMargin: 10
                            Layout.leftMargin: 5
                            width: 200 * mainwindow.baseScale
                            height: 200 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter
                            color: "transparent"

                            Image {
                                id: devImage
                                anchors.fill: parent

                                sourceSize.width: 200 * mainwindow.baseScale
                                sourceSize.height: 200 * mainwindow.baseScale

                                source: (devImage.status === Image.Error) ? "../images/icons/capybaraIcon.png" : Nimage
                            }
                        }
                        Text {
                            Layout.leftMargin: 10
                            Layout.maximumWidth: mainwindow.width_1 * 14 * mainwindow.baseScale
                            Layout.maximumHeight: mainwindow.height_1 * 4 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter

                            horizontalAlignment: Text.AlignHCenter
                            text: Ntitle
                            wrapMode: Text.Wrap
                            clip: true

                            font.bold: true
                            font.pixelSize: 18 * mainwindow.baseScale
                            color: mainTextColor
                        }
                        Text {
                            Layout.leftMargin: 10
                            Layout.maximumWidth: mainwindow.width_1 * 14 * mainwindow.baseScale
                            Layout.maximumHeight: mainwindow.height_1 * 10 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter

                            horizontalAlignment: Text.AlignHCenter
                            text: Ndescription
                            wrapMode: Text.Wrap
                            clip: true

                            font.pixelSize: 16 * mainwindow.baseScale
                            color: mainTextColor
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onHoveredChanged: (mouse)=> {
                            if(!isHovered.visible)
                            {
                                isHovered.visible = true;
                            }
                            else
                            {
                                isHovered.visible = false;
                            }
                        }
                        onClicked: {
                            if(Qt.LeftButton){
                                qmlArticle.htmlAdress = Narticle;
                                qmlArticle.show = true;
                            }
                        }
                    }
                }
            }
        }
    }

    ListView {
        id: communityNews
        y: mainwindow.height_1 * 36 * mainwindow.baseScale
        width: Window.width - 1080
        height: mainwindow.height_1 * 35 * mainwindow.baseScale
        clip: true
        orientation: Qt.Horizontal
        flickableDirection: Flickable.HorizontalFlick
        model: News {
            list: cCommunityNewsList
        }

        delegate: Item {
            width: mainwindow.width_1 * 15 * mainwindow.baseScale
            Row {
                id: communityNews_row
                Rectangle{
                    id: communityNews_rectangle
                    width: mainwindow.width_1 * 15 * mainwindow.baseScale
                    height: mainwindow.height_1 * 35 * mainwindow.baseScale
                    color: "transparent"
                    ColumnLayout {
                        Rectangle {
                            property bool isHovered: false
                            Layout.topMargin: 10
                            Layout.leftMargin: 10
                            width: 200 * mainwindow.baseScale
                            height: 200 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter
                            color: "transparent"

                            Image {
                                id: comImage
                                anchors.fill: parent

                                sourceSize.width: 200 * mainwindow.baseScale
                                sourceSize.height: 200 * mainwindow.baseScale

                                source: (devImage.status === Image.Error) ? "../images/icons/capybaraIcon.png" : Nimage
                            }
                        }
                        Text {
                            Layout.leftMargin: 10
                            Layout.maximumWidth: mainwindow.width_1 * 14 * mainwindow.baseScale
                            Layout.maximumHeight: mainwindow.height_1 * 4 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter

                            horizontalAlignment: Text.AlignHCenter
                            text: Ntitle
                            wrapMode: Text.Wrap
                            clip: true

                            font.bold: true
                            font.pixelSize: 18 * mainwindow.baseScale
                            color: mainTextColor
                        }
                        Text {
                            Layout.leftMargin: 10
                            Layout.maximumWidth: mainwindow.width_1 * 14 * mainwindow.baseScale
                            Layout.maximumHeight: mainwindow.height_1 * 10 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter

                            horizontalAlignment: Text.AlignHCenter
                            text: Ndescription
                            wrapMode: Text.Wrap
                            clip: true

                            font.pixelSize: 16 * mainwindow.baseScale
                            color: mainTextColor
                        }
                    }
                    Rectangle {
                        id: isHoveredC
                        anchors.fill: parent
                        visible: false
                        color: mainwindow.rectangleColor
                        border.color: mainwindow.rectangleBorder
                        border.width: 1
                    }
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            isHoveredC = true
                        }
                        onExited: {
                            isHoveredC = false
                        }
                        onClicked: {
                            if(Qt.LeftButton){
                                qmlArticle.htmlAdress = Narticle;
                                qmlArticle.show = true;
                            }
                        }
                    }
                }
            }
        }
    }
    function devRefreshNewsList() {
        developerCANews.model.refreshList();
    }

    function communityRefreshNewslist() {
        communityNews.model.refreshList();
    }
}
