import QtQuick

import cNews

Item {
    x: 1100
    y: 100
    id: right_panel
    enabled : rightPanelEnabled
    //Loader {
    //    id: root
    //    source: "http://localhost:5000/get_component_data?component_id=RemoteComponent"
    //    onLoaded: {
    //        root.width = root.item.width
    //        root.height = root.item.height
    //    }
    //}

    TableView {
        id: developerCANews
        width: 2000
        height: 300
        clip: true
        flickableDirection: Flickable.HorizontalFlick
        model: News {
            list: cDevNewsList
        }
        delegate: Item {
            Row {
                Repeater {
                    model: cDevNewsList
                    delegate: Column {
                        x: 250
                        id: gameNews_row1
                        spacing: 10
                        Rectangle {
                            width: 10
                            height: 10
                            color: "red"
                        }
                    }
                }
            }
        }
    }
    //ListView {
    //    id: communityNews
    //    x: 0
    //    y: 360
    //    width: Window.width - 1080
    //    height: 320
    //    clip: true
    //    orientation: Qt.Horizontal
    //    flickableDirection: Flickable.HorizontalFlick
    //    model: ListModel {
    //        ListElement {
    //            name: "Grey"
    //            colorCode: "grey"
    //        }

    //        ListElement {
    //            name: "Red"
    //            colorCode: "red"
    //        }

    //        ListElement {
    //            name: "Blue"
    //            colorCode: "blue"
    //        }

    //        ListElement {
    //            name: "Green"
    //            colorCode: "green"
    //        }
    //    }
    //    delegate: Item {
    //        width: 300
    //        height: 300
    //        Row {
    //            x: 50
    //            id: laucherNews_row
    //            spacing: 10
    //            Rectangle {
    //                width: 200
    //                height: 200
    //                color: colorCode
    //                Text {
    //                    width: 280
    //                    height: 95
    //                    x: -50
    //                    y: parent.height + 10
    //                    text: qsTr("A simle informations about news aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc01lp")
    //                    wrapMode: Text.WrapAnywhere
    //                    clip: true
    //                    font.bold: true
    //                    font.pixelSize: 16
    //                    color: mainTextColor
    //                }
    //            }
    //        }
    //    }
    //}
}
