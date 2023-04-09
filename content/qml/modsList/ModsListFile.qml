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
            id: mainItem
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
                    width: 90
                    text: (local_hover2 && globalActionMenuOpen === false) ? steam_packname.implicitWidth <= steam_packname.width ? modgameid : "" : modgameid
                    clip: true
                    font.bold: true
                    font.pixelSize: 16
                    color: ((local_hover || local_hover2 || mouseRow) && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                }
                Rectangle {
                    width: 15
                    height: 15
                    color: "transparent"
                    Image {
                        anchors.fill: parent
                        source: "../../images/icons/hand2.png"
                    }
                    MouseArea {
                        id: drag
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: (mouse)=>{
                                   }
                        onHoveredChanged: (mouse)=>{
                            if(containsMouse){
                                parent.color = "#00FFFFFF"
                            }
                            else
                            {
                                parent.color = "transparent"
                            }
                        }
                    }
                }
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
                width: 920
                height: 34
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                property point position: mapToGlobal(mouseX, mouseY);
                onClicked: (mouse)=> {
                    if (mouse.button === Qt.RightButton)
                    {
                        globalActionMenuOpen = true;

                        mousePositionX = position.x;
                        mousePositionY = position.y;
                        qmlModsListClickMenu.currentName = model.name;
                        qmlModsListClickMenu.currentPackname = model.packname;
                        qmlModsListClickMenu.currentId = model.modgameid;
                        qmlModsListClickMenu.currentIndexPos = model.id;
                        if (model.colorWarn.r === 0.8823529481887817 && model.colorWarn.g === 0.8823529481887817 && model.colorWarn.b === 0)
                        {
                             updateAvailable = true;
                        }
                        else
                        {
                            updateAvailable = false;
                        }
                        qmlModsListClickMenu.visible = true;
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
            MouseArea {
                x: 920
                y: -6
                width: 40
                height: 34
                acceptedButtons: Qt.RightButton
                property point defCursPosition: Qt.point(0, 0)
                property point cursPosition: Qt.point(0, 0)
                onPressed: {
                    defCursPosition = mapToGlobal(mouseX, mouseY);
                }
                onPositionChanged: {
                    cursPosition = mapToGlobal(mouseX, mouseY);

                    var dy = defCursPosition.y - cursPosition.y
                    if (dy > parent.height) {
                        defCursPosition = cursPosition;
                        modsList.model.move(index, index-1)
                    }
                    else if(dy < -parent.height){
                        defCursPosition = cursPosition;
                        modsList.model.move(index, index+1)
                    }
                }
            }
        }
    }

    ModsList_Top{
        id: qmlModsListTop
    }

    ModsList_ClickMenu{
        id: qmlModsListClickMenu
        z: 1
    }

    ModsList_Right{
        id: qmlModsListRight
    }

    function setIndex(index){
        modsList.currentIndex = index;
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
}
