import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebView

Item {
    id: articleIN
    property url htmlAdress: ""
    property bool show: false
    visible: show
    x: mainwindow.width_1 * 10 * mainwindow.baseScale
    y: mainwindow.height_1 * 5 * mainwindow.baseScale
    width: mainwindow.width_1 * 80 * mainwindow.baseScale
    height: mainwindow.height_1 * 90 * mainwindow.baseScale
    Rectangle{
        anchors.fill: parent
        color: "#CFCFCF"
        WebView {
            id: webView
            anchors.fill: parent
            anchors.centerIn: parent

            url: htmlAdress
        }
        ToolBar {
            x: parent.x
            y: parent.y - mainwindow.height_1 * 3 * mainwindow.baseScale
            width: parent.width
            height: mainwindow.height_1 * 3 * mainwindow.baseScale
            id: navigationBar
            RowLayout {
                anchors.fill: parent
                spacing: 0

                ToolButton {
                    id: backButton
                    icon.source: "../images/icons/arrowBlackLeft64.png"
                    onClicked: webView.goBack()
                    enabled: webView.canGoBack
                    Layout.preferredWidth: navigationBar.height
                }

                ToolButton {
                    id: forwardButton
                    icon.source: "../images/icons/arrowBlackRight64.png"
                    onClicked: webView.goForward()
                    enabled: webView.canGoForward
                    Layout.preferredWidth: navigationBar.height
                }

                ToolButton {
                    id: reloadButton
                    icon.source: "../images/icons/refreshIcon64.png"
                    onClicked: webView.loading ? webView.stop() : webView.reload()
                    Layout.preferredWidth: navigationBar.height
                }

                Item { Layout.preferredWidth: 5 }

                TextField {
                    Layout.fillWidth: true
                    id: urlField
                    inputMethodHints: Qt.ImhUrlCharactersOnly | Qt.ImhPreferLowercase
                    text: webView.url
                    onAccepted: webView.url = utils.fromUserInput(text)
                 }

                Item { Layout.preferredWidth: 5 }

                ToolButton {
                    id: goButton
                    text: qsTr("Go")
                    onClicked: {
                        Qt.inputMethod.commit()
                        Qt.inputMethod.hide()
                        webView.url = backWebEngine.fromUserInput(urlField.text)
                    }
                }

                Item { Layout.preferredWidth: 10 }

                ToolButton {
                    id: downloadButton
                    icon.source: "../images/icons/downloadGreen.png"
                    onClicked: {
                        if(Qt.LeftButton){
                            qtGeneralBackendObj.addMod(backWebEngine.downloadModFromUrl(urlField.text));
                            objModsList.refreshModlistVector();
                            qmlModsList.refreshModlist();
                        }
                    }

                    Layout.preferredWidth: navigationBar.height
                }

                Item { Layout.preferredWidth: 10 }

                ToolButton {
                    id: closeButton
                    text: qsTr("X")
                    onClicked: {
                        if(Qt.LeftButton)
                        {
                            show = false;
                        }
                    }
                }

                Item { Layout.preferredWidth: 10 }
             }
        }
    }
}
