import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

//import customModules

Rectangle {
    id: actionMenu
    property int currentIndexPos
    property string currentName
    property string currentPackname
    property string currentId

    x: qmlModsList.mousePositionX - 25
    y: ((qmlModsList.mousePositionY - 50) < (mainwindow.height - 350)) ? qmlModsList.mousePositionY - 50 : qmlModsList.mousePositionY - 325
    width: 500 * mainwindow.baseScale
    height: 350 * mainwindow.baseScale
    visible: actionMenuHovered.hovered
    Rectangle {
        anchors.fill: parent
        color: mainwindow.rectangleColor
        border.width: 1
        border.color: mainwindow.rectangleBorder
        ColumnLayout {
            anchors.fill: parent
            Text {
                Layout.maximumHeight: 20 * mainwindow.baseScale
                Layout.maximumWidth: 480 * mainwindow.baseScale
                Layout.alignment: Qt.AlignCenter
                font.pixelSize: 16 * mainwindow.baseScale
                font.bold: true
                color: mainwindow.mainTextColor
                clip: true
                text: currentName !== "Local mod" ? currentName : currentPackname
            }
            RowLayout{
                Layout.maximumHeight: 30 * mainwindow.baseScale
                Layout.alignment: Qt.AlignCenter
                visible: (currentId !== "0" && updateAvailable) ? true : false
                Text {
                    font.pixelSize: 16 * mainwindow.baseScale
                    font.bold: true
                    color: mainwindow.mainTextColor
                    text: "Update available"
                    Rectangle {
                        x: parent.implicitWidth + 5
                        width: 25 * mainwindow.baseScale
                        height: 25 * mainwindow.baseScale
                        color: "transparent"
                        Image {
                            anchors.fill: parent
                            source: "../../images/icons/downloadGreen.png"
                        }
                    }
                    Item {
                        x: parent.x - 10
                        y: parent - 5
                        width: parent.width + 40
                        height: parent.height + 5
                        Rectangle {
                            anchors.fill: parent
                            color: "#2DFFFFFF"
                            visible: updateHovered.hovered
                        }
                        HoverHandler {
                            id: updateHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(Qt.LeftButton){
                                    qmlModsList.setIndex(currentIndexPos);
                                    qtGeneralBackendObj.updateMod(currentId);
                                }
                            }
                        }
                    }
                }
            }
            GridLayout {
                Layout.preferredWidth: 500 * mainwindow.baseScale
                columns: 2
                rows: 4
                rowSpacing: 10
                Rectangle {
                    id: openInBrowser
                    Layout.column: 0
                    Layout.row: 0
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter
                    visible: currentId !== "0"

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: openInBrowserHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Open in Browser")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: openInBrowserHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                Qt.openUrlExternally("https://steamcommunity.com/sharedfiles/filedetails/?id=" + currentId);
                            }
                        }
                    }
                }
                Rectangle {
                    id: openInSteam
                    Layout.column: 0
                    Layout.row: 1
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter
                    visible: currentId !== "0"

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: openInSteamHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Open in Steam")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: openInSteamHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                Qt.openUrlExternally("steam://openurl/https://steamcommunity.com/sharedfiles/filedetails/?id=" + currentId)
                            }
                        }
                    }
                }
                Rectangle {
                    id: unsubscribe
                    Layout.column: 0
                    Layout.row: 2
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter
                    visible: currentId !== "0"

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: unsubscribeHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Unsubscribe")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: unsubscribeHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                qmlModsList.setIndex(currentIndexPos);
                                qtGeneralBackendObj.removeMod(currentId);
                                objModsList.refreshModlistVector();
                                qmlModsList.refreshModlist();                            }
                        }
                    }
                }
                Rectangle {
                    id: resubscribe
                    Layout.column: 0
                    Layout.row: 3
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter
                    visible: currentId !== "0"

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: resubscribeHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Resubscribe")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: resubscribeHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                qmlModsList.setIndex(currentIndexPos);
                                qtGeneralBackendObj.removeMod(currentId);
                                qtGeneralBackendObj.addTask(currentId, "addMod");
                                objModsList.refreshModlistVector();
                                qmlModsList.refreshModlist();                           }
                        }
                    }
                }
                Rectangle {
                    id: copyName
                    Layout.column: 1
                    Layout.row: 0
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter
                    visible: currentId !== "0"

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: copyNameHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Copy Name")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: copyNameHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                textEdit.text = currentName;
                                textEdit.selectAll();
                                textEdit.copy();
                            }
                        }
                    }
                }
                // >---------------- LOCAL MOD REPLACE 1:0
                Rectangle {
                    id: removeLocal
                    Layout.column: 1
                    Layout.row: 0
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter
                    visible: currentId === "0"

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: removeLocalHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Remove Copy")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: removeLocalHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                qmlModsList.setIndex(currentIndexPos);
                                qtGeneralBackendObj.removeLocalCopy(currentIndexPos);
                                objModsList.refreshModlistVector();
                                qmlModsList.refreshModlist();
                            }
                        }
                    }
                }
                // <---------------- LOCAL MOD REPLACE 1:0
                Rectangle {
                    id: openLocalFiles
                    Layout.column: 1
                    Layout.row: 1
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: openLocalFilesHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Open Files")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: openLocalFilesHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                qmlModsList.setIndex(currentIndexPos);
                                qtGeneralBackendObj.openLocalFiles(currentIndexPos);
                            }
                        }
                    }
                }
                Rectangle {
                    id: openPack
                    Layout.column: 1
                    Layout.row: 2
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: openPackHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Open Pack")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: openPackHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                qmlModsList.setIndex(currentIndexPos);
                                qtGeneralBackendObj.openInRPFM(currentIndexPos);
                            }
                        }
                    }
                }
                Rectangle {
                    id: makeLocalCopy
                    Layout.column: 1
                    Layout.row: 3
                    Layout.preferredWidth: 120 * mainwindow.baseScale
                    Layout.preferredHeight: 30 * mainwindow.baseScale
                    Layout.alignment: Qt.AlignCenter
                    visible: currentId !== "0"

                    color: mainwindow.rectangleColor
                    border.width: 1
                    border.color: mainwindow.rectangleBorder
                    Rectangle {
                        anchors.fill: parent
                        color: "#2DFFFFFF"
                        visible: makeLocalCopyHovered.hovered
                    }

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 13 * mainwindow.baseScale
                        font.bold: true
                        color: mainwindow.mainTextColor
                        text: qsTr("Make Local Copy")
                    }
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: makeLocalCopyHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Qt.LeftButton){
                                qmlModsList.setIndex(currentIndexPos);
                                qtGeneralBackendObj.makeLocalCopy(currentId);
                                objModsList.refreshModlistVector();
                                qmlModsList.refreshModlist();
                            }
                        }
                    }
                }
            }
        }
    }
    Item {
        anchors.fill: parent
        HoverHandler {
            id: actionMenuHovered
            acceptedDevices: PointerDevice.Mouse
            cursorShape: Qt.PointingHandCursorw
            onHoveredChanged: {
                if(!hovered){
                    actionMenu.visible = false;
                    qmlModsList.globalActionMenuOpen = false;
                }
            }
        }
    }
}
