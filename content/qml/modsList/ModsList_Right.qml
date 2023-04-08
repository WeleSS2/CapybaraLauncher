import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 1.3

Item {
    x: 980
    y: 100
    ColumnLayout{
        Rectangle {
            id: openGoogle
            width: 35 * mainwindow.baseScale
            height: 35 * mainwindow.baseScale
            Layout.alignment: Qt.AlignTop
            color: "transparent"
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
            Image {
                id: openGoogleImage
                anchors.fill: parent
                source: "../../images/icons/google.png"
            }
        }
    }
}
