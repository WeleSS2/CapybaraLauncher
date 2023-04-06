import QtQuick
import QtQuick.Controls

Item {
    visible: ObjInfoBox.boxStatus

    Rectangle {
        id: qt_box
        x: ObjInfoBox.xPos != 0 ? ObjInfoBox.xPos : (mainwindow.width / 2) - (this.width / 2)
        y: ObjInfoBox.yPos != 0 ? ObjInfoBox.yPos : (mainwindow.height / 2) - (this.height / 2)
        width: qt_boxText.implicitWidth + 20
        height: ObjInfoBox.containButton ? qt_boxText.implicitHeight + 70 : qt_boxText.implicitHeight + 20

        Text {
            id: qt_boxText
            x: 10
            y: 10
            text: ObjInfoBox.boxText
            Connections {
                    target: ObjInfoBox
                    function onPingBoxText() {
                        qt_boxText.text = ObjInfoBox.boxText;
                    }
                }
        }

        Button {
            id: qt_boxButton
            visible: ObjInfoBox.containButton
            x: (parent.width / 2) - (qt_boxButton.implicitWidth / 2)
            y: 50
            text: ObjInfoBox.buttonText
        }
    }
}
