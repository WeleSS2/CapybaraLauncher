import QtQuick
import QtQuick.Controls

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
