import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import cGameChangerListUrl

Rectangle {
    x: 100
    y: 100
    width: parent.width - 200
    height: parent.height - 200
    visible: false
    color: mainwindow.rectangleColor
    border.width: 1
    border.color: mainwindow.rectangleBorder

    property int defaultGame: 11

    Button {
        id: closeSettings
        x: parent.width - 30
        y: 0
        width: 30
        height: 30
        text: "X"
        onClicked: {
            if(Qt.LeftButton){
                qmlTopMenu.enableLeftRightBottom();
                parent.visible = false;
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        Rectangle {
            id: selectDefaultGameRec
            color: "transparent"
            Layout.alignment: Qt.AlignLeft
            Layout.fillWidth: true
            height: 40

            Text {
                id: selectDefaultGameText
                text: "Select default game (Disabled temporary)"
                color: mainwindow.mainTextColor
                font.pointSize: 14

                //ComboBox {
                //    id: selectDefaultGame
                //    x: parent.implicitWidth + 5
                //    y: parent.y + 5
                //    editable: false
                //    model: GameChanger {
                //        list: ObjcGameChangerList
                //    }

                //    onActivated: {
                //        qmlGameSelector.setGame(currentIndex);
                //        qtGeneralBackendObj.saveDefaultGame();
                //    }
                //}
            }
        }
        Rectangle {
            id: unsafeModeRec
            color: "transparent"
            Layout.alignment: Qt.AlignLeft
            Layout.fillWidth: true
            height: 40

            Text {
                id: unsafeModeText
                text: "Enable unsafe mode"
                color: mainwindow.mainTextColor
                font.pointSize: 14

                Rectangle {
                    x: unsafeModeText.implicitWidth + 5
                    y: 5
                    width: 20
                    height: 20
                    color: qtGeneralBackendObj.unsafeMode ? "green" : "white"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: (mouse)=>{
                            if(!qtGeneralBackendObj.unsafeMode){
                                parent.color = "green";
                                qtGeneralBackendObj.unsafeMode = true;
                            }
                            else
                            {
                                parent.color = "white";
                                qtGeneralBackendObj.unsafeMode = false;
                            }
                        }
                    }
                }
            }
        }
        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft
        }
    }



    function showSettings(){
        if(!qmlSettingsModule.visible){
            qmlSettingsModule.visible = true
        }
    }
}
