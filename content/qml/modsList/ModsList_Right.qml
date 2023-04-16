import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 1.3

import "../customModules"

Item {
    x: 980
    y: 100
    enabled: !qmlModsList.globalActionMenuOpen
    ColumnLayout{
        spacing: 10
        z: parent.z
        CustomButton {
            id: searchMods
            z: parent.z
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            //color: "transparent"
            bBackground.visible: false
            bText.visible: false
            bImage.visible: true
            bImage.source: "../../images/icons/search.png"
            bDesc: "Find mod"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton){
                        //TODO
                        if(textInputRect.visible)
                        {
                            textInputRect.visible = false;
                            rightPanelEnabled = true;
                            qmlModsList.z = 0;
                        }
                        else
                        {
                            textInputRect.visible = true;
                            rightPanelEnabled = false;
                            qmlModsList.z = 2;
                            textEdit.focus = true;
                        }
                    }
                }
            }
        }
        CustomButton {
            id: multipleModsOptions
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            //color: "transparent"
            bBackground.visible: false
            bImage.source: "../../images/icons/dots.png"
            bDesc: "Multiple mods options"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton)
                    {
                        // TODO show menu for selected mods
                    }
                    else if(Qt.RightButton)
                    {
                        // TODO show menu for all mods
                    }
                }
            }
        }

        CustomButton {
            id: updateAllMods
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            //color: "transparent"
            bBackground.visible: false
            bImage.source: "../../images/icons/downloadGreen.png"
            bDesc: "Update all mods"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton)
                    {
                        qtGeneralBackendObj.addTask(0, "updateAllMods");
                    }
                }
            }
        }

        CustomButton {
            id: openGoogle
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            //color: "transparent"
            bBackground.visible: false
            bText.visible: false
            bImage.visible: true
            bImage.source: "../../images/icons/google.png"
            bDesc: "Open google"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton)
                    {
                        qmlArticle.htmlAdress = "https://www.google.com";
                        qmlArticle.show = true;
                    }
                }
            }
        }
    }

    CustomButton {
        id: textInputRect
        x: -200
        y: -30
        width: 230
        height: 30
        //color: "transparent"
        visible: false
        bText.visible: false
        bImage.visible: false
        bHover: false
        TextEdit {
            id: textEdit
            x: 5
            width: 200
            height: 30
            font.pointSize: 15
            focus: true
            clip: true
            color: mainwindow.mainTextColor
            text: ""
            onTextChanged: {
                qmlModsList.findMod(this.text);
                qmlModsList.refreshModlist();
            }
        }
        CustomButton {
            x: parent.x + 170
            width: 30
            height: 30
            //color: "transparent"
            bImage.visible: false
            bText.text: "X"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    textEdit.text = "";
                    textInputRect.visible = false;
                    rightPanelEnabled = true;
                    qmlModsList.z = 0;
                }
            }
        }
    }
}
