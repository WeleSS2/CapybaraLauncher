import QtQuick
import QtQuick.Controls

Rectangle {
    id: holder
    visible: false
    x: (mainScreen.width / 2)
    y: (mainScreen.height / 2)
    width: infoBoxText.width + 40
    height: infoBoxText.height + 20

    Connections {
        target: infoBox
        onChangedEnabled: {
            holder.visible = infoBox.enabled
            infoBoxText.text = infoBox.infoText
            holder.x = infoBox.xPos === 0 ? (mainScreen.width / 2) : infoBox.xPos
            holder.x = infoBox.yPos === 0 ? (mainScreen.height / 2) : infoBox.yPos
        }
    }
    Text {
        id: infoBoxText
        text: infoBox.infoText
    }
}
