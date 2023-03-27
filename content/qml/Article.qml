import QtQuick
import QtQuick.Controls
import QtWebView

Item {
    id: articleIN
    property url htmlAdress: ""
    property bool show: false
    visible: show
    x: mainwindow.width_1 * 20 * mainwindow.baseScale
    y: mainwindow.height_1 * 5 * mainwindow.baseScale
    width: mainwindow.width_1 * 60 * mainwindow.baseScale
    height: mainwindow.height_1 * 90 * mainwindow.baseScale
    Rectangle{
        anchors.fill: parent
        color: "#CFCFCF"
        WebView {
            id: webview
            anchors.fill: parent

            //url: "https://raw.githubusercontent.com/WeleSS2/CapybaraNEWS/main/1142710/DEV_25.03.2023_CapybaraTestRelease/CapyHTML.html"
            url: "https://https://doc.qt.io/qt-6/qtwebview-index.html"
        }
        Button {
            x: parent.width - 25
            y: parent.y + 5
            height: 25 * mainwindow.baseScale
            width: 25 * mainwindow.baseScale
            onClicked: {
                if(Qt.LeftButton)
                {
                    articleIN.show = false;
                }
            }
        }
    }
}
