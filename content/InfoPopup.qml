import QtQuick
import QtQuick.Controls

Item {
    Popup {
        x: Window.width / 2 - 250
        y: Window.height / 2 - 150
        width: 500
        height: 250
        contentItem: Text {
                text: "Content"
            }
    }
}
