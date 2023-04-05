import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    x: mainwindow.width_1 * 3 * mainwindow.baseScale
    y: mainwindow.height_1 * 3 * mainwindow.baseScale
    width: mainwindow.width_1 * 94 * mainwindow.baseScale
    height: mainwindow.height_1 * 2 * mainwindow.baseScale
    property int elementWidth: mainwindow.width_1 * 9
    visible: qmlArticle.show
    ListModel {
        id: openedSites
    }

    ListView {
        id: openTabs

        anchors.fill: parent
        clip: true
        orientation: Qt.Horizontal
        flickableDirection: Flickable.HorizontalFlick

        model: openedSites

        delegate: Item {
            width: elementWidth
            height: parent.height
            Rectangle {
                anchors.fill: parent
                Text {
                    anchors.fill: parent
                    text: name
                }
            }
        }
    }
}
