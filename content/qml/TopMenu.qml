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
        Rectangle {
            id: launcherupdate
            Layout.minimumWidth: width
            Layout.maximumWidth: Layout.preferredWidth
            width: 35 * mainwindow.baseScale
            height: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            color: "transparent"
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    if(updatestatus){
                        launcherupdateImage.source = "../images/icons/downloadGreenLight.png";
                    }
                    else
                    {
                        launcherupdateImage.source = "../images/icons/downloadRed.png";
                    }
                }
                onExited: {
                    if(updatestatus){
                        launcherupdateImage.source = "../images/icons/downloadGreen.png";
                    }
                    else
                    {
                        launcherupdateImage.source = "../images/icons/downloadRed.png";
                    }
                }
                onClicked: {
                    if(Qt.LeftButton){
                        if(updatestatus)
                        {
                            qtGeneralBackendObj.updateLauncher();
                        }
                    }
                }
            }
            Image {
                id: launcherupdateImage
                anchors.fill: parent
                source: parent.parent.updatestatus ? "../images/icons/downloadGreen.png" : "../images/icons/downloadRed.png"
            }
        }

        Rectangle {
            id: discord
            width: 35 * mainwindow.baseScale
            height: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            color: "transparent"
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if(Qt.LeftButton){
                        Qt.openUrlExternally("https://discord.gg/vkb8FCFZP6")
                    }
                }
                onEntered: {
                    discordImage.source = "../images/icons/discordLight.png";
                }
                onExited: {
                    discordImage.source = "../images/icons/discord.png";
                }
            }
            Image {
                id: discordImage
                anchors.fill: parent
                source: "../images/icons/discord.png"
            }
        }

        Rectangle {
            id: patreon
            width: 35 * mainwindow.baseScale
            height: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            color: "transparent"
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if(Qt.LeftButton){
                        Qt.openUrlExternally("https://patreon.com/CapybaraStudio")
                    }
                }
                onEntered: {
                    patreonImage.source = "../images/icons/patreonLight.png";
                }
                onExited: {
                    patreonImage.source = "../images/icons/patreon.png";
                }
            }
            Image {
                id: patreonImage
                anchors.fill: parent
                source: "../images/icons/patreon.png"
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
