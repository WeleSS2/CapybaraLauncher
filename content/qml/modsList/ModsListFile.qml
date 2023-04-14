import QtQuick
import QtQuick.Controls 2.5

import cMods

Item {
    id: mainMouseArea
    anchors.fill: parent
    property bool globalActionMenuOpen: false
    property bool updateAvailable: false
    property int baseW: 1000
    property int mousePositionX
    property int mousePositionY
    enabled: modListEnabled

    ListView {
        id: modsList
        x: 8
        y: 130
        width: baseW
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
            id: mod
            height: 40
            width: 950
            property bool local_hover
            property bool local_hover2
            property string copiedText
            Rectangle {
                y: -6
                width: 950
                height: 38
                id: modBackground
                color: modHovered.hovered ? "#A4070707" : "transparent"
                visible: true
                HoverHandler {
                    id: modHovered
                    enabled: modListEnabled && globalActionMenuOpen === false
                    acceptedDevices: PointerDevice.Mouse
                    cursorShape: Qt.PointingHandCursor
                }
            }
            Row {
                spacing: 10
                x: 5
                Text {
                    id: lau_id
                    width: this.implicitWidth > 20 ? this.implicitWidth : 20
                    text: (Number(id) + 1).toString()
                    clip: true
                    font.bold: true
                    font.pixelSize: 16
                    color: (modHovered.hovered && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                }
                CheckBox {
                    id: mod_id
                    checked: model.done
                    indicator: Rectangle {
                        y: 5
                        width: 15
                        height: 15
                        color: mod_id.checked ? "green" : "white"
                    }
                }
                Text {
                    id: steam_name
                    width: 300
                    x: -225
                    text: name
                    clip: (steamNameHovered.hovered && !globalActionMenuOpen) ? false : true
                    font.bold: true
                    font.pixelSize: 16
                    color: (modHovered.hovered && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: steamNameHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }
                Text {
                    id: steam_date
                    width: 100
                    text: (steamNameHovered.hovered && globalActionMenuOpen === false) ? steam_name.implicitWidth <= steam_name.width ? date : "" : date
                    clip: true
                    font.bold: true
                    font.pixelSize: 16
                    color: (modHovered.hovered && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                }
                Text {
                    id: steam_packname
                    width: 325
                    text: (steamNameHovered.hovered && globalActionMenuOpen === false) ? steam_name.implicitWidth <= steam_name.width + steam_date.width ? packname : "" : packname
                    clip: (steamPacknameHovered.hovered && !globalActionMenuOpen) ? false : true
                    font.bold: true
                    font.pixelSize: 16
                    color: (modHovered.hovered && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                    Item {
                        anchors.fill: parent
                        HoverHandler {
                            id: steamPacknameHovered
                            acceptedDevices: PointerDevice.Mouse
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }
                Text {
                    id: steamId
                    width: 90
                    text: (steamPacknameHovered.hovered && globalActionMenuOpen === false) ? steam_packname.implicitWidth <= steam_packname.width ? modgameid : "" : modgameid
                    clip: true
                    font.bold: true
                    font.pixelSize: 16
                    color: (modHovered.hovered && !globalActionMenuOpen) ? highlightTextColor : colorWarn
                }
                Rectangle {
                    y: 5
                    width: 15
                    height: 15
                    color: "transparent"
                    Image {
                        anchors.fill: parent
                        source: "../../images/icons/hand2.png"
                    }
                }
            }
            Canvas {
                id: rowSplitter
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
                height: 38
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                property point position: mapToGlobal(mouseX, mouseY);
                onClicked: (mouse)=> {
                    if (mouse.button === Qt.RightButton)
                    {
                        globalActionMenuOpen = true;
                        rightPanelEnabled = false;
                        qmlModsList.z = 1;

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
                            if(!mod_id.checked && !model.done)
                            {
                                enableMod(model.id);
                                mod_id.checked = true;
                            }
                            else
                            {
                                disableMod(model.id);
                                mod_id.checked = false;
                            }
                        }
                    }
                }
            }
            MouseArea {
                x: 920
                y: -6
                width: 30
                height: 34
                acceptedButtons: Qt.RightButton
                property point defCursPosition: Qt.point(0, 0)
                property point cursPosition: Qt.point(0, 0)
                onPressed: {
                    defCursPosition = mapToGlobal(mouseX, mouseY);
                }
                onReleased: {
                    refreshModlist();
                }
                onPositionChanged: {
                    cursPosition = mapToGlobal(mouseX, mouseY);

                    var dy = defCursPosition.y - cursPosition.y
                    if (dy > parent.height - 7) {
                        defCursPosition = cursPosition;
                        modsList.model.move(index, index-1)
                    }
                    else if(dy < -parent.height + 3){
                        defCursPosition = cursPosition;
                        modsList.model.move(index, index+2)
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

    property int returnedIndex
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

    function enableMod(id){
        modsList.model.enableMod(id);
    }

    function disableMod(id){
        modsList.model.disableMod(id);
    }

    function findMod(key){
        modsList.model.findMod(key);
    }

    function onEnable(){
        objModsList.sortByActive();
        qmlModsList.refreshModlist();
    }
}
