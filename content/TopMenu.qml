import QtQuick
import QtQuick.Controls

Item {
    Button {
        id: gamesite
        x: Window.width - 550
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
        x: Window.width - 400
        y: 0
        width: 120
        height: 30
        font.pixelSize: 20
        text: qsTr("Workshop")
        onClicked: {
            if(Qt.LeftButton){
                Qt.openUrlExternally("https://steamcommunity.com/app/1142710/workshop/")
            }
        }
    }
    Button {
        id: settings
        x: Window.width - 250
        y: 0
        width: 120
        height: 30
        font.pixelSize: 20
        text: qsTr("Settings")

        onClicked: {
            if(Qt.LeftButton){
                settingsModule.showSettings();
            }
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
}
