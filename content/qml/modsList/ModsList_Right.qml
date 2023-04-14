import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 1.3

import "../customModules"

Item {
    x: 980
    y: 100
    ColumnLayout{
        spacing: 10
        CustomButton {
            id: searchMods
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            color: "transparent"
            bBackground.visible: false
            bText.visible: false
            bImage.visible: true
            bImage.source: "../../images/icons/search.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(Qt.LeftButton){
                        //TODO
                    }
                }
            }
        }

        CustomButton {
            id: openGoogle
            Layout.preferredWidth: 35 * mainwindow.baseScale
            Layout.preferredHeight: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignRight
            color: "transparent"
            bBackground.visible: false
            bText.visible: false
            bImage.visible: true
            bImage.source: "../../images/icons/google.png"
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





}
