import QtQuick
import QtQuick.Layouts

import "../customModules"

Rectangle {
    id: actionMenu
    x: 1020
    y: 100
    visible: false
    width: 500 * mainwindow.baseScale
    height: 400 * mainwindow.baseScale
    color: mainwindow.rectangleColor
    border.width: 1
    border.color: mainwindow.rectangleBorder
    property int buttonsWidth: 120 * mainwindow.baseScale
    property int buttonsHeight: 30 * mainwindow.baseScale
    property int buttonsTextSize: 15 * mainwindow.baseScale
    ColumnLayout {
        Text {
            Layout.maximumHeight: 20 * mainwindow.baseScale
            Layout.alignment: Qt.AlignCenter
            font.pixelSize: 16 * mainwindow.baseScale
            font.bold: true
            color: mainwindow.mainTextColor
            clip: true
            text: "Action for seleceted mods"
        }
        GridLayout {
            Layout.preferredWidth: 500 * mainwindow.baseScale
            columns: 1
            rows: 5
            rowSpacing: 10
            CustomButton {
                id: updateAllMods
                Layout.column: 0
                Layout.row: 0
                Layout.preferredWidth: 120 * mainwindow.baseScale
                Layout.preferredHeight: 30 * mainwindow.baseScale
                Layout.alignment: Qt.AlignCenter
                bImage.visible: false
                bText.font.pixelSize: 13 * mainwindow.baseScale
                bText.text: qsTr("Update mods")
                onClicked: { // Add update for selected and all mods

                }
            }

        }
    }
}
