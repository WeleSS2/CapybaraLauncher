import QtQuick
import QtQuick.Controls 2.5

import cMods

Item {
    id: mainMouseArea
    anchors.fill: parent
    property bool globalActionMenuOpen: false
    property bool updateAvailable: false
    property int baseW: 1200
    property int mousePositionX
    property int mousePositionY
    property int currentIndexPos
    property string currentName
    property string currentId
    property alias overModList : overModList
    enabled: modListEnabled

    ListView {
        id: modsList
        x: 8
        y: 130
        width: 1200
        height: mainwindow.height - 150
        clip: true
        Component.onCompleted: {
                // Set the pointer to the ListView instance
                objModsList.setListViewPointer(modsList);
        }
        model: Mods {
            list: objModsList
        }


        delegate: Item {
            x: 5
            height: 40
            property bool local_hover
            property bool local_hover2
            property bool mouseRow
            property string copiedText
            MouseArea {
                y: -8
                x: 0
                width: 925
                height: 38
                hoverEnabled: true
                onHoveredChanged: (mouse)=> {
                   if(!mouseRow)
                       {
                           mouseRow = true;
                       }
                       else
                       {
                           mouseRow = false;
                       }
                }
            }
            Row {
                spacing: 10
                Text {
                    id: lau_id
                    width: this.implicitWidth > 20 ? this.implicitWidth : 20
                    text: (Number(id) + 1).toString()
                    clip: true
                    font.bold: true
                    font.pixelSize: 16
                    color: ((local_hover || local_hover2 || mouseRow) && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                }
                CheckBox {
                    id: mod_id
                    checked: model.done
                    indicator: Rectangle {
                        y: 5
                        width: 15
                        height: 15
                        color: model.done ? "green" : "white"
                    }
                }
                Text {
                    id: steam_name
                    width: 300
                    x: -225
                    text: name
                    clip: (local_hover && !globalActionMenuOpen) ? false : true
                    font.bold: true
                    font.pixelSize: 16
                    color: ((local_hover || local_hover2 || mouseRow) && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                    MouseArea {
                        y: -8
                        width: 315
                        height: 38
                        hoverEnabled: true
                        onHoveredChanged: (mouse)=> {
                             if(!local_hover)
                                 {
                                     local_hover = true;
                                 }
                                 else
                                 {
                                     local_hover = false;
                                 }
                          }
                    }
                }
                Text {
                    id: steam_date
                    width: 100
                    text: (local_hover && globalActionMenuOpen === false) ? steam_name.implicitWidth <= steam_name.width ? date : "" : date
                    clip: true
                    font.bold: true
                    font.pixelSize: 16
                    color: ((local_hover || local_hover2 || mouseRow) && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                }
                Text {
                    id: steam_packname
                    width: 325
                    text: (local_hover && globalActionMenuOpen === false) ? steam_name.implicitWidth <= steam_name.width + steam_date.width ? packname : "" : packname
                    clip: (local_hover2 && !globalActionMenuOpen) ? false : true
                    font.bold: true
                    font.pixelSize: 16
                    color: ((local_hover || local_hover2 || mouseRow) && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                    MouseArea {
                        y: -8
                        width: 315
                        height: 38
                        hoverEnabled: true
                        onHoveredChanged: (mouse)=> {
                             if(!local_hover2)
                                 {
                                     local_hover2 = true;
                                 }
                                 else
                                 {
                                     local_hover2 = false;
                                 }
                          }
                    }
                }
                Text {
                    width: 150
                    text: (local_hover2 && globalActionMenuOpen === false) ? steam_packname.implicitWidth <= steam_packname.width ? modgameid : "" : modgameid
                    clip: true
                    font.bold: true
                    font.pixelSize: 16
                    color: ((local_hover || local_hover2 || mouseRow) && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                }
                //Text {
                //    width: 200
                //    text: model.author
                //    anchors.verticalCenter: parent.verticalCenter
                //    clip: true
                //    font.bold: true
                //    font.pixelSize: 16
                //    color: ((local_hover || local_hover2 || mouseRow) && !globalActionMenuOpen) ? highlightTextColor : mainTextColor
                //}

            }
            Canvas {
                id: mycanvas
                width: 1000
                height: 60
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.fillStyle = Qt.rgba(0.3, 0.3, 0.3, 1);
                    ctx.fillRect(0, 32, 950, 2);
                    this.requestPaint();
                }
            }

            MouseArea {
                y: -6
                width: 950
                height: 34
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                property point position: mapToGlobal(mouseX, mouseY);
                onClicked: (mouse)=> {
                      if (mouse.button === Qt.RightButton)
                      {
                          if(!globalActionMenuOpen)
                          {
                               mousePositionX = position.x;
                               mousePositionY = position.y;
                               currentName = model.name;
                               currentId = model.modgameid;
                               currentIndexPos = model.id;
                               if (model.colorWarn.r === 0.8823529481887817 && model.colorWarn.g === 0.8823529481887817 && model.colorWarn.b === 0)
                               {
                                    updateAvailable = true;
                               }
                               else
                               {
                                   updateAvailable = false;
                               }
                               actionMenu.visible = true;
                          }
                          else
                          {
                              globalActionMenuOpen = false;
                              actionMenu.visible = false;

                              mousePositionX = position.x;
                              mousePositionY = position.y;
                              currentName = model.name;
                              currentId = model.modgameid;
                              currentIndexPos = model.id;
                              if (model.colorWarn.r === 0.8823529481887817 && model.colorWarn.g === 0.8823529481887817 && model.colorWarn.b === 0)
                              {
                                  updateAvailable = true;
                              }
                              else
                              {
                                  updateAvailable = false;
                              }
                              actionMenu.visible = true;
                          }
                      }
                      else if (mouse.button === Qt.LeftButton)
                      {
                          if(!globalActionMenuOpen)
                          {
                              if(!mod_id.checked)
                              {
                                  mod_id.checked = true;
                                  model.done = true;
                              }
                              else
                              {
                                  mod_id.checked = false;
                                  model.done = false;
                              }
                          }
                      }
                  }
            }
        }
    }

    Rectangle {
        id: overModList
        y: 100

        property alias enableCanvas : enableCanvas
        property alias nameCanvas : nameCanvas
        property alias dateCanvas : dateCanvas
        property alias packnameCanvas : packnameCanvas
        Text {
            width: 62
            height: 30
            x: 25
            text: qsTr("Enable")
            font.bold: true
            font.pixelSize: 16
            color: mainTextColor
            Canvas{
                id: enableCanvas
                width: 30
                height:30
                x: (parent.implicitWidth / 2) - 20
                y: -20

                property bool clicked: false

                onPaint:{
                     var context = getContext("2d");
                     context.reset();
                     // the triangle
                     context.beginPath();
                     context.moveTo(11, clicked ? 10 : 20);
                     context.lineTo(29, clicked ? 10 : 20);
                     context.lineTo(20, clicked ? 20 : 10);
                     context.closePath();


                     // the fill color
                     context.fillStyle = clicked ? "red" : "#FFCC00";
                     context.fill();
                }
                MouseArea {
                    width: 50
                    height: 50
                    x: -10
                    y: -10
                    onClicked: (mouse)=>{
                                   objModsList.sortByActive();
                                   refreshModlistTo0();
                                   onEnable();
                                   clearCanvases();
                                   parent.clicked = true;
                                   parent.requestPaint();
                               }
                }
            }
        }

        Text {
            width: 108
            height: 30
            x: 190
            text: qsTr("Mod Name")
            font.bold: true
            font.pixelSize: 16
            color: mainTextColor
            Canvas{
                id: nameCanvas
                width: 30
                height:30
                x: (parent.implicitWidth / 2) - 20
                y: -20

                property bool clicked: false

                onPaint:{
                     var context = getContext("2d");
                     context.reset();
                     // the triangle
                     context.beginPath();
                     context.moveTo(11, clicked ? 10 : 20);
                     context.lineTo(29, clicked ? 10 : 20);
                     context.lineTo(20, clicked ? 20 : 10);
                     context.closePath();


                     // the fill color
                     context.fillStyle = clicked ? "red" : "#FFCC00";
                     context.fill();
                }
                MouseArea {
                    width: 50
                    height: 50
                    x: -10
                    y: -10
                    onClicked: (mouse)=>{
                                   objModsList.sortByName();
                                   refreshModlistTo0();
                                   clearCanvases();
                                   parent.clicked = true;
                                   parent.requestPaint();
                               }
                }
            }
        }

        Text {
            x: 387
            width: 108
            height: 30
            color: mainTextColor
            text: qsTr("Update Date")
            font.pixelSize: 16
            font.bold: true
            Canvas{
                id: dateCanvas
                width: 30
                height:30
                x: (parent.implicitWidth / 2) - 20
                y: -20

                property bool clicked: false

                onPaint:{
                     var context = getContext("2d");
                     context.reset();
                     // the triangle
                     context.beginPath();
                     context.moveTo(11, clicked ? 10 : 20);
                     context.lineTo(29, clicked ? 10 : 20);
                     context.lineTo(20, clicked ? 20 : 10);
                     context.closePath();


                     // the fill color
                     context.fillStyle = clicked ? "red" : "#FFCC00";
                     context.fill();
                }
                MouseArea {
                    width: 50
                    height: 50
                    x: -10
                    y: -10
                    onClicked: (mouse)=>{
                                   objModsList.sortByDate();
                                   refreshModlistTo0();
                                   clearCanvases();
                                   parent.clicked = true;
                                   parent.requestPaint();
                               }
                }
            }
        }

        Text {
            x: 610
            width: 108
            height: 30
            color: mainTextColor
            text: qsTr("Packname")
            font.pixelSize: 16
            font.bold: true
            Canvas{
                id: packnameCanvas
                width: 30
                height:30
                x: (parent.implicitWidth / 2) - 20
                y: -20

                property bool clicked: false

                onPaint:{
                     var context = getContext("2d");
                     context.reset();
                     // the triangle
                     context.beginPath();
                     context.moveTo(11, clicked ? 10 : 20);
                     context.lineTo(29, clicked ? 10 : 20);
                     context.lineTo(20, clicked ? 20 : 10);
                     context.closePath();


                     // the fill color
                     context.fillStyle = clicked ? "red" : "#FFCC00";
                     context.fill();
                }
                MouseArea {
                    width: 50
                    height: 50
                    x: -10
                    y: -10
                    onClicked: (mouse)=>{
                                   objModsList.sortByPackname();
                                   refreshModlistTo0();
                                   clearCanvases();
                                   parent.clicked = true;
                                   parent.requestPaint();
                               }
                }
            }
        }

        Text {
            x: 860
            width: 108
            height: 30
            color: mainTextColor
            text: qsTr("Mod ID")
            font.pixelSize: 16
            font.bold: true
        }

        Rectangle {
            id: refreshButton
            x: 980
            width: 30
            height: 30
            color: "transparent"
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    if(Qt.LeftButton){
                        objModsList.refreshModlistVector();
                        refreshModlistTo0();
                    }
                }
                onEntered: {
                    refreshButtonImage.source = "images/icons/refreshIcon64Light.png"
                }
                onExited: {
                    refreshButtonImage.source = "images/icons/refreshIcon64.png"
                }
            }
            Image {
                id: refreshButtonImage
                anchors.fill: parent
                source: "images/icons/refreshIcon64.png"
            }
        }

        //Text {
        //    x: 977
        //    y: 100
        //    width: 108
        //    height: 30
        //    color: mainTextColor
        //    text: qsTr("Author")
        //    font.pixelSize: 16
        //    clip: true
        //    font.bold: true
        //}
    }

    Rectangle {
        id: actionMenu
        x: mousePositionX - 25
        y: ((mousePositionY - 40) < (mainScreen.height - 400)) ? mousePositionY - 40 : mousePositionY - 350
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
                        if(position.x > actionMenu.x + 200 || position.x < actionMenu.x + 25
                           || position.y > actionMenu.y + 350 || position.y < actionMenu.y + 40)
                        {
                            actionMenu.visible = false;
                            globalActionMenuOpen = false;
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
            text:  currentName
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
                textEdit.text = currentName
                textEdit.selectAll()
                textEdit.copy()
            }
        }

        Button {
            visible: currentId !== "0"
            id: modsListFile_Button_Unsubscribe
            x: 10
            y: currentId !== "0" ?  modsListFile_Button_CopyClipboard.y + 30 : 0
            text: "Unsubscribe"
            onClicked: {
                modsList.currentIndex = currentIndexPos;
                qtGeneralBackendObj.removeMod(currentId);
                objModsList.refreshModlistVector();
                refreshModlist();
            }
        }

        Button {
            visible: currentId !== "0"
            id: modsListFile_Button_Resubscribe
            x: 10
            y: currentId !== "0" ?  modsListFile_Button_Unsubscribe.y + 30 : 0
            text: "Resubsribe"
            onClicked: {
                modsList.currentIndex = currentIndexPos;
                qtGeneralBackendObj.removeMod(currentId);
                qtGeneralBackendObj.addMod(currentId);
                objModsList.refreshModlistVector();
                refreshModlist();
            }
        }

        Button {
            visible: currentId !== "0" && updateAvailable
            id: modsListFile_Button_UpdateMod
            x: 10
            y: (currentId !== "0" && updateAvailable) ? modsListFile_Button_Resubscribe.y + 30 : modsListFile_Button_Resubscribe.y
            text: "Update mod"
            onClicked: {
                modsList.currentIndex = currentIndexPos;
                qtGeneralBackendObj.updateMod(currentId);
            }
        }

        Button {
            id: modsListFile_Button_OpenLocalFiles
            x: 10
            y: modsListFile_Button_UpdateMod.y + 30
            text: "Open Local Files"
            onClicked: {
                modsList.currentIndex = currentIndexPos;
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
                modsList.currentIndex = currentIndexPos;
                qtGeneralBackendObj.makeLocalCopy(currentId);
                objModsList.refreshModlistVector();
                refreshModlist();
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
                modsList.currentIndex = currentIndexPos;
                qtGeneralBackendObj.removeLocalCopy(currentIndexPos);
                objModsList.refreshModlistVector();
                refreshModlist();
            }
        }

        // Local only
        Button {
            id: modsListFile_Button_OpenRPFM
            x: 10
            y: currentId === "0" ? modsListFile_Button_Remove.y + 30 : modsListFile_Button_MakeLocalCopy.y + 30
            text: "Open packfile"
            onClicked: {
                modsList.currentIndex = currentIndexPos;
                qtGeneralBackendObj.openInRPFM(currentIndexPos);
            }
        }
    }
    function refreshModlist() {
        modsList.model.refreshList();
    }
    function refreshModlistTo0(){
        modsList.currentIndex = 0;
        modsList.model.refreshList();
    }

    function onEnable(){
        objModsList.sortByActive();
        qmlModsList.refreshModlist();
    }

    function clearCanvases(){
        enableCanvas.clicked = false;
        enableCanvas.requestPaint();
        nameCanvas.clicked = false;
        nameCanvas.requestPaint();
        dateCanvas.clicked = false;
        dateCanvas.requestPaint();
        packnameCanvas.clicked = false;
        packnameCanvas.requestPaint();
    }
}
