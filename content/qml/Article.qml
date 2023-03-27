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
            anchors.centerIn: parent

            url: htmlAdress
        }
        Button {
            id: closeWebView
            x: parent.width
            y: -2
            width: 30 * mainwindow.baseScale
            height: 30 * mainwindow.baseScale
            text: "X"
            onClicked: {
                if(Qt.LeftButton)
                {
                    show = false;
                }
            }
        }
    }
}
