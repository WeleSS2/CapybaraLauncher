import QtQuick

Item {
    id: right_panel
    enabled : rightPanelEnabled
    ListView {
        id: developerCANews
        x: 1075
        y: 100
        width: Window.width - 1080
        height: 300
        clip: true
        orientation: Qt.Horizontal
        flickableDirection: Flickable.HorizontalFlick
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        delegate: Item {
            width: 300
            height: 300
            Row {
                x: 50
                id: gameNews_row
                spacing: 10
                Rectangle {
                    width: 200
                    height: 200
                    color: colorCode
                    Text {
                        width: 280
                        height: 95
                        x: -50
                        y: parent.height + 10
                        text: qsTr("A simle informations about news aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc01lp")
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
        x: 1075
        y: 460
        width: Window.width - 1080
        height: 320
        clip: true
        orientation: Qt.Horizontal
        flickableDirection: Flickable.HorizontalFlick
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        delegate: Item {
            width: 300
            height: 300
            Row {
                x: 50
                id: laucherNews_row
                spacing: 10
                Rectangle {
                    width: 200
                    height: 200
                    color: colorCode
                    Text {
                        width: 280
                        height: 95
                        x: -50
                        y: parent.height + 10
                        text: qsTr("A simle informations about news aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc01lp")
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
