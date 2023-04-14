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
        width: Window.width - 1080 * mainwindow.baseScale
        height: 350 * mainwindow.baseScale
        spacing: 10 * mainwindow.baseScale
        clip: true
        flickableDirection: Flickable.HorizontalFlick
        orientation: Qt.Horizontal
        model: News {
            list: cDevNewsList
        }

        delegate: Item {
            width: 300 * mainwindow.baseScale
            height: 350 * mainwindow.baseScale
            Row {
                id: developerCANews_row
                spacing: 20
                Rectangle{
                    id: developerCANews_rectangle
                    width: 300 * mainwindow.baseScale
                    height: 350 * mainwindow.baseScale
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
                            Layout.maximumWidth: 280 * mainwindow.baseScale
                            Layout.maximumHeight: 50 * mainwindow.baseScale
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
                            Layout.maximumWidth: 280 * mainwindow.baseScale
                            Layout.maximumHeight: 100 * mainwindow.baseScale
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
                            if(rightPanelEnabled)
                            {
                                if(!isHovered.visible)
                                {
                                    isHovered.visible = true;
                                }
                                else
                                {
                                    isHovered.visible = false;
                                }
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
        y: 360 * mainwindow.baseScale
        width: Window.width - 1080 * mainwindow.baseScale
        height: 350 * mainwindow.baseScale
        spacing: 10 * mainwindow.baseScale
        clip: true
        orientation: Qt.Horizontal
        flickableDirection: Flickable.HorizontalFlick
        model: News {
            list: cCommunityNewsList
        }

        delegate: Item {
            width: 300 * mainwindow.baseScale
            height: 350 * mainwindow.baseScale
            Row {
                id: communityNews_row
                spacing: 20
                Rectangle{
                    id: communityNews_rectangle
                    width: 300 * mainwindow.baseScale
                    height: 350 * mainwindow.baseScale
                    color: "transparent"
                    Rectangle {
                        id: isHoveredC
                        anchors.fill: parent
                        visible: false
                        color: mainwindow.rectangleColor
                        border.color: mainwindow.rectangleBorder
                        border.width: 1
                    }
                    ColumnLayout {
                        Layout.alignment: Qt.AlignCenter
                        Rectangle {
                            Layout.topMargin: 10
                            width: 200 * mainwindow.baseScale
                            height: 200 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter
                            color: "transparent"

                            Image {
                                id: comImage
                                anchors.fill: parent

                                sourceSize.width: 200 * mainwindow.baseScale
                                sourceSize.height: 200 * mainwindow.baseScale

                                source: (comImage.status === Image.Error) ? "../images/icons/capybaraIcon.png" : Nimage
                            }
                        }
                        Text {
                            Layout.leftMargin: 10
                            Layout.maximumWidth: 280 * mainwindow.baseScale
                            Layout.maximumHeight: 50 * mainwindow.baseScale
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
                            Layout.maximumWidth: 280 * mainwindow.baseScale
                            Layout.maximumHeight: 100 * mainwindow.baseScale
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
                        enabled: !qmlModListOptions.menuActive
                        hoverEnabled: true
                        onHoveredChanged: (mouse)=> {
                            if(!isHoveredC.visible)
                            {
                                isHoveredC.visible = true;
                            }
                            else
                            {
                                isHoveredC.visible = false;
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
    function devRefreshNewsList() {
        developerCANews.model.refreshList();
    }

    function communityRefreshNewsList() {
        communityNews.model.refreshList();
    }
}
