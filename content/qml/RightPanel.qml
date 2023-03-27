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
        height: 300
        clip: true
        flickableDirection: Flickable.HorizontalFlick
        orientation: Qt.Horizontal
        model: News {
            list: cDevNewsList
        }

        delegate: Item {
            width: mainwindow.width_1 * 15 * mainwindow.baseScale
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
        x: 0
        y: 360
        width: Window.width - 1080
        height: 320
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
                spacing: 20
                Rectangle{
                    id: communityNews_rectangle
                    width: mainwindow.width_1 * 15 * mainwindow.baseScale
                    height: mainwindow.height_1 * 35 * mainwindow.baseScale
                    color: "transparent"
                    ColumnLayout {
                        Image {
                            id: comImage
                            Layout.alignment: Qt.AlignCenter

                            width: 200 * mainwindow.baseScale
                            height: 200 * mainwindow.baseScale
                            source: Nimage
                            onStatusChanged: if (comImage.status === Image.Error || comImage.status === Image.Null) comImage.source = "../images/icons/capybaraIcon.png"
                        }
                        Text {
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
}
