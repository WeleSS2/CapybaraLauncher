import QtQuick
import QtQuick.Controls

Item {
    Button {
        id: gamesite
        x: Window.width - 600
        y: 0
        width: 120
        height: 30
        font.pixelSize: 20
        text: qsTr("Gamesite")
        onClicked: {
           if(Qt.LeftButton)
               {
                   Qt.openUrlExternally("https://warhammer3.totalwar.com")
               }
           }
    }
    Button {
        id: workshop
        x: Window.width - 450
        y: 0
        width: 120
        height: 30
        font.pixelSize: 20
        text: qsTr("Workshop")
        onClicked: {
            if(Qt.LeftButton){
                Qt.openUrlExternally("steam://openurl/https://steamcommunity.com/app/1142710/workshop/")
            }
        }
    }
    Button {
        id: settings
        x: Window.width - 300
        y: 0
        width: 120
        height: 30
        font.pixelSize: 20
        text: qsTr("Settings")

        onClicked: {
            if(Qt.LeftButton){
                disableLeftRightBottom();
                settingsModule.showSettings();
            }
        }
    }

    property bool updatestatus: qtGeneralBackendObj.updateAvialable()
    Rectangle {
        id: launcherupdate
        x: parent.parent.width - 135
        y: 0
        width: 35
        height: 35
        color: "transparent"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                if(updatestatus){
                    launcherupdateImage.source = "images/icons/downloadGreenLight.png";
                }
                else
                {
                    launcherupdateImage.source = "images/icons/downloadRed.png";
                }
            }
            onExited: {
                if(updatestatus){
                    launcherupdateImage.source = "images/icons/downloadGreen.png";
                }
                else
                {
                    launcherupdateImage.source = "images/icons/downloadRed.png";
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
            source: updatestatus ? "images/icons/downloadGreen.png" : "images/icons/downloadRed.png"
        }
    }

    Rectangle {
        id: discord
        x: parent.parent.width - 90
        y: 0
        width: 35
        height: 35
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
                discordImage.source = "images/discordLight.png";
            }
            onExited: {
                discordImage.source = "images/discord.png";
            }
        }
        Image {
            id: discordImage
            anchors.fill: parent
            source: "images/discord.png"
        }
    }

    Rectangle {
        id: patreon
        x: parent.parent.width - 45
        y: 0
        width: 35
        height: 35
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
                patreonImage.source = "images/patreonLight.png";
            }
            onExited: {
                patreonImage.source = "images/patreon.png";
            }
        }
        Image {
            id: patreonImage
            anchors.fill: parent
            source: "images/patreon.png"
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
