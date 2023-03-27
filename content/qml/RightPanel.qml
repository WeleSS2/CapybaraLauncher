import QtQuick
import QtQuick.Layouts

import cNews

Item {
    x: 1000
    y: 100
    id: right_panel
    enabled : rightPanelEnabled

    ListView {
        id: developerCANews
        width: Window.width - 1080
        height: mainwindow.height_1 * 35 * mainwindow.baseScale
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
                    ColumnLayout {
                        Rectangle {
                            Layout.topMargin: 10
                            Layout.leftMargin: 10
                            width: 200 * mainwindow.baseScale
                            height: 200 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter

                            Image {
                                id: devImage
                                anchors.fill: parent

                                sourceSize.width: 200 * mainwindow.baseScale
                                sourceSize.height: 200 * mainwindow.baseScale

                                source: Nimage
                                onStatusChanged: if (devImage.status === Image.Error || devImage.status === Image.Null) devImage.source = "../images/icons/capybaraIcon.png"
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
                        onEntered: {
                            developerCANews_rectangle.color = "black"
                        }
                        onExited: {
                            developerCANews_rectangle.color = "transparent"
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
                            Layout.topMargin: 10
                            Layout.leftMargin: 10
                            width: 200 * mainwindow.baseScale
                            height: 200 * mainwindow.baseScale
                            Layout.alignment: Qt.AlignCenter

                            Image {
                                id: comImage
                                anchors.fill: parent

                                sourceSize.width: 200 * mainwindow.baseScale
                                sourceSize.height: 200 * mainwindow.baseScale

                                source: Nimage
                                onStatusChanged: if (comImage.status === Image.Error || comImage.status === Image.Null) comImage.source = "../images/icons/capybaraIcon.png"
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
                        onEntered: {
                            communityNews_rectangle.color = "black"
                        }
                        onExited: {
                            communityNews_rectangle.color = "transparent"
                        }
                    }
                }
            }
        }
    }
    function refreshNewslist() {
        developerCANews.model.refreshList();
        //communityNews.model.refreshList();
    }
}
