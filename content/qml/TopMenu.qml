import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import content
import "customModules"

Item {
    property bool updatestatus: qtGeneralBackendObj.updateAvialable()
    GridLayout {
        x: mainwindow.width_1 * 75 * mainwindow.baseScale
        width: mainwindow.width_1 * 25 * mainwindow.baseScale
        columns: 5
        rows: 1
        CustomButton {
            id: workshop
            Layout.preferredWidth: 120 * mainwindow.baseScale
            Layout.preferredHeight: 30 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            bImage.visible: false
            bText.font.pixelSize: 20 * mainwindow.baseScale
            bText.text: qsTr("Workshop")


            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton){
                        Qt.openUrlExternally("steam://openurl/https://steamcommunity.com/app/" + qmlGameSelector.currentGameId.toString() + "/workshop/")
                    }
                }
            }
        }
        CustomButton {
            id: settings
            Layout.preferredWidth: 120 * mainwindow.baseScale
            Layout.preferredHeight: 30 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            bImage.visible: false
            bText.font.pixelSize: 20 * mainwindow.baseScale
            bText.text: qsTr("Settings")

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton){
                        disableLeftRightBottom();
                        qmlSettingsModule.showSettings();
                    }
                }
            }
        }
        CustomButton {
            id: launcherupdate
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            //color: "transparent"
            bBackground.visible: false
            bImage.source: updatestatus === true ? "../../images/icons/downloadGreen.png" : "../../images/icons/downloadRed.png"
            bDesc: "Update launcher"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton){
                        if(updatestatus)
                        {
                            qtGeneralBackendObj.addTask(0, "updateLauncher");
                        }
                    }
                }
            }
        }

        CustomButton {
            id: discord
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            //color: "transparent"
            bBackground.visible: false
            bImage.source: "../../images/icons/discord.png"
            bDesc: "Open discord"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton){
                        Qt.openUrlExternally("https://discord.gg/vkb8FCFZP6")
                    }
                }
            }
        }

        CustomButton {
            id: patreon
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            //color: "transparent"
            bBackground.visible: false
            bImage.source: "../../images/icons/patreon.png"
            bDesc: "Open patreon"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton){
                        Qt.openUrlExternally("https://patreon.com/CapybaraStudio")
                    }
                }
            }
        }
    }

    function disableLeftRightBottom(){
        modListEnabled = false
        rightPanelEnabled = false
        bottomGameMenuEnabled = false
    }
    function enableLeftRightBottom(){
        modListEnabled = true
        rightPanelEnabled = true
        bottomGameMenuEnabled = true
    }
}
