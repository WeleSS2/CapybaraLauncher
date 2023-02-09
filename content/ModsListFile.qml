import QtQuick
import QtQuick.Controls 2.5
import WH3_Mod_Menager

import CModsList

MouseArea {
    id: mainMouseArea
    anchors.fill: parent
    property bool globalActionMenuOpen: false
    property int baseW: 1200
    property int mousePositionX
    property int mousePositionY
    property string currentName
    property string currentId
    property alias overModList : overModList

    ListView {
        id: modsList
        x: 8
        y: 130
        width: 1200
        height: mainwindow.height - 150
        clip: true
        model: CModsListFile {
            list: Objcmodslistfilling
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
                    text: id
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
                                   Objcmodslistfilling.sortByActive();
                                   refreshModlist();


                                   onEnable();
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
                                   Objcmodslistfilling.sortByName();
                                   refreshModlist();
                                   parent.clicked = true;
                                   parent.requestPaint();
                                   enableCanvas.clicked = false;
                                   enableCanvas.requestPaint();
                                   //nameCanvas.clicked = false;
                                   //nameCanvas.requestPaint();
                                   dateCanvas.clicked = false;
                                   dateCanvas.requestPaint();
                                   packnameCanvas.clicked = false;
                                   packnameCanvas.requestPaint();
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
                                   Objcmodslistfilling.sortByDate();
                                   refreshModlist();
                                   parent.clicked = true;
                                   parent.requestPaint();
                                   enableCanvas.clicked = false;
                                   enableCanvas.requestPaint();
                                   nameCanvas.clicked = false;
                                   nameCanvas.requestPaint();
                                   //dateCanvas.clicked = false;
                                   //dateCanvas.requestPaint();
                                   packnameCanvas.clicked = false;
                                   packnameCanvas.requestPaint();
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
                                   Objcmodslistfilling.sortByPackname();
                                   refreshModlist();
                                   parent.clicked = true;
                                   parent.requestPaint();
                                   enableCanvas.clicked = false;
                                   enableCanvas.requestPaint();
                                   nameCanvas.clicked = false;
                                   nameCanvas.requestPaint();
                                   dateCanvas.clicked = false;
                                   dateCanvas.requestPaint();
                                   //packnameCanvas.clicked = false;
                                   //packnameCanvas.requestPaint();
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
        y: mousePositionY - 40
        width: 175
        height: 250
        visible: false
        HoverHandler {
            id: mouse2
            acceptedDevices: PointerDevice.Mouse
            cursorShape: Qt.PointingHandCursor

            onHoveredChanged: (mouse2)=> {
                 if(actionMenu.visible)
                 {
                     if(globalActionMenuOpen)
                     {
                          globalActionMenuOpen = false;
                          actionMenu.visible = false;
                     }
                     else
                     {
                         globalActionMenuOpen = true;
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
            x: 15
            y: 35
            text: "Open in Browser"
            onClicked: {
                Qt.openUrlExternally("https://steamcommunity.com/sharedfiles/filedetails/?id=" + currentId);
            }
        }
        Button {
            x: 15
            y: 65
            text: "Open in Steam"
            onClicked: {
                Qt.openUrlExternally("steam://openurl/https://steamcommunity.com/sharedfiles/filedetails/?id=" + currentId)
            }
        }

        TextEdit{
                id: textEdit
                visible: false
            }
        Button {
            x: 15
            y: 95
            text: "Copy name to clipboard"
            onClicked: {
                textEdit.text = currentName
                textEdit.selectAll()
                textEdit.copy()
            }
        }
    }
    function refreshModlist() {
        modsList.model.refreshList();
    }

    function onEnable(){
        Objcmodslistfilling.sortByActive();
        modlist.refreshModlist();
        enableCanvas.clicked = true;
        enableCanvas.requestPaint();
        nameCanvas.clicked = false;
        nameCanvas.requestPaint();
        dateCanvas.clicked = false;
        dateCanvas.requestPaint();
        packnameCanvas.clicked = false;
        packnameCanvas.requestPaint();
    }
}
