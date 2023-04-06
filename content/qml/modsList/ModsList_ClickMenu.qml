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
                                qtGeneralBackendObj.addMod(currentId);
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
/*
Rectangle {
    id: actionMenu

    property int currentIndexPos
    property string currentName
    property string currentPackname
    property string currentId

    x: qmlModsList.mousePositionX - 25
    y: ((qmlModsList.mousePositionY - 40) < (mainwindow.height - 400)) ? qmlModsList.mousePositionY - 40 : qmlModsList.mousePositionY - 350
    width: 200
    height: 350
    visible: false
    MouseArea {
        id: mouse2
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        hoverEnabled: true
        property point position: mapToGlobal(mouseX, mouseY);
        onHoveredChanged: (mouse2)=> {
             position = mapToGlobal(mouseX, mouseY);
             if(actionMenu.visible){
                if(position.x !== 0){
                    if(position.x > actionMenu.x + 175 || position.x < actionMenu.x + 25
                       || position.y > actionMenu.y + 350 || position.y < actionMenu.y + 40)
                    {
                        actionMenu.visible = false;
                        qmlModsList.globalActionMenuOpen = false;
                    }
                }
            }
        }
    }
    Text {
        x: 5
        y: 5
        width: 165
        clip: true
        text: currentName !== "Local mod" ? currentName : currentPackname
    }

    Button {
        visible: currentId !== "0"
        id: modsListFile_Button_OpenBrowser
        x: 10
        y: currentId !== "0" ? 35 : 0
        text: "Open in Browser"
        onClicked: {
            Qt.openUrlExternally("https://steamcommunity.com/sharedfiles/filedetails/?id=" + currentId);
        }
    }
    Button {
        visible: currentId !== "0"
        id: modsListFile_Button_OpenSteam
        x: 10
        y: currentId !== "0" ? modsListFile_Button_OpenBrowser.y + 30 : 0
        text: "Open in Steam"
        onClicked: {
            Qt.openUrlExternally("steam://openurl/https://steamcommunity.com/sharedfiles/filedetails/?id=" + currentId)
        }
    }

    Button {
        visible: currentId !== "0"
        id: modsListFile_Button_CopyClipboard
        x: 10
        y: currentId !== "0" ? modsListFile_Button_OpenSteam.y + 30 : 0
        text: "Copy name to clipboard"
        onClicked: {
            textEdit.text = currentName;
            textEdit.selectAll();
            textEdit.copy();
        }
    }

    Button {
        visible: currentId !== "0"
        id: modsListFile_Button_Unsubscribe
        x: 10
        y: currentId !== "0" ?  modsListFile_Button_CopyClipboard.y + 30 : 0
        text: "Unsubscribe"
        onClicked: {
            qmlModsList.setIndex(currentIndexPos);
            qtGeneralBackendObj.removeMod(currentId);
            objModsList.refreshModlistVector();
            qmlModsList.refreshModlist();
        }
    }

    Button {
        visible: currentId !== "0"
        id: modsListFile_Button_Resubscribe
        x: 10
        y: currentId !== "0" ?  modsListFile_Button_Unsubscribe.y + 30 : 0
        text: "Resubsribe"
        onClicked: {
            qmlModsList.setIndex(currentIndexPos);
            qtGeneralBackendObj.removeMod(currentId);
            qtGeneralBackendObj.addMod(currentId);
            objModsList.refreshModlistVector();
            qmlModsList.refreshModlist();
        }
    }

    Button {
        visible: currentId !== "0" && updateAvailable
        id: modsListFile_Button_UpdateMod
        x: 10
        y: (currentId !== "0" && updateAvailable) ? modsListFile_Button_Resubscribe.y + 30 : modsListFile_Button_Resubscribe.y
        text: "Update mod"
        onClicked: {
            qmlModsList.setIndex(currentIndexPos);
            qtGeneralBackendObj.updateMod(currentId);
        }
    }

    Button {
        id: modsListFile_Button_OpenLocalFiles
        x: 10
        y: modsListFile_Button_UpdateMod.y + 30
        text: "Open Local Files"
        onClicked: {
            qmlModsList.setIndex(currentIndexPos);
            qtGeneralBackendObj.openLocalFiles(currentIndexPos);
        }
    }

    // Steam only
    Button {
        visible: currentId !== "0"
        id: modsListFile_Button_MakeLocalCopy
        x: 10
        y: currentId !== "0" ? modsListFile_Button_OpenLocalFiles.y + 30 : 0
        text: "Make local copy"
        onClicked: {
            qmlModsList.setIndex(currentIndexPos);
            qtGeneralBackendObj.makeLocalCopy(currentId);
            objModsList.refreshModlistVector();
            qmlModsList.refreshModlist();
        }
    }

    // Local Only
    Button {
        visible: currentId === "0"
        id: modsListFile_Button_Remove
        x: 10
        y: currentId === "0" ? modsListFile_Button_OpenLocalFiles.y + 30 : 0
        text: "Remove"
        onClicked: {
            qmlModsList.setIndex(currentIndexPos);
            qtGeneralBackendObj.removeLocalCopy(currentIndexPos);
            objModsList.refreshModlistVector();
            qmlModsList.refreshModlist();
        }
    }

    Button {
        id: modsListFile_Button_OpenRPFM
        x: 10
        y: currentId === "0" ? modsListFile_Button_Remove.y + 30 : modsListFile_Button_MakeLocalCopy.y + 30
        text: "Open packfile"
        onClicked: {
            qmlModsList.setIndex(currentIndexPos);
            qtGeneralBackendObj.openInRPFM(currentIndexPos);
        }
    }
}
*/
