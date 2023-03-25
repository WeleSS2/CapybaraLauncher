import QtQuick

import cNews

Item {
    x: 1100
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
            width: 300
            height: 50
            Row {
                id: developerCANews_row
                spacing: 20
                Rectangle {
                    width: 200
                    height: 200
                    color: colorCode
                    Text {
                        width: 280
                        height: 95
                        y: parent.height + 10
                        text: article
                        wrapMode: Text.WrapAnywhere
                        clip: true
                        font.bold: true
                        font.pixelSize: 16
                        color: mainTextColor
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
            width: 300
            height: 50
            Row {
                id: communityNews_row
                spacing: 20
                Rectangle {
                    width: 200
                    height: 200
                    color: colorCode
                    Text {
                        width: 280
                        height: 95
                        y: parent.height + 10
                        text: article
                        wrapMode: Text.WrapAnywhere
                        clip: true
                        font.bold: true
                        font.pixelSize: 16
                        color: mainTextColor
                    }
                }
            }
        }
    }
}
