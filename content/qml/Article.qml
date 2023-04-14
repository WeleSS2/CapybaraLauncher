import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebView

Item {
    id: articleIN
    property url htmlAdress: ""
    property bool show: false
    visible: show
    x: mainwindow.width_1 * 2 * mainwindow.baseScale
    y: mainwindow.height_1 * 6 * mainwindow.baseScale
    width: mainwindow.width_1 * 96 * mainwindow.baseScale
    height: mainwindow.height_1 * 91 * mainwindow.baseScale
    Rectangle{
        anchors.fill: parent
        color: "#CFCFCF"
        Rectangle {
            y: parent.y
            id: recWebView
            anchors.fill: parent
            anchors.centerIn: parent

            WebView {
                id: webView
                anchors.fill: parent
                anchors.centerIn: parent

                url: htmlAdress

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                    onReleased: {
                        if (mouse.button === Qt.RightButton) {
                            var menu = webView.contextMenu
                            menu.clear()
                            var newTabAction = menu.addAction("Open Link in New Tab")
                            newTabAction.triggered.connect(addElementToList)
                            menu.popup()
                        }
                    }
                }
            }
        }


        ToolBar {
            x: parent.x
            y: parent.y - (mainwindow.height_1 * 3 * mainwindow.baseScale)
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
                        htmlAdress = backWebEngine.fromUserInput(urlField.text)
                    }
                }

                Item { Layout.preferredWidth: 10 }

                ToolButton {
                    id: downloadButton
                    icon.source: "../images/icons/downloadGreen.png"
                    onClicked: {
                        if(Qt.LeftButton){
                            if(backWebEngine.downloadModFromUrl(urlField.text) !== 0)
                            {
                                console.log("Add mod 1");
                                qtGeneralBackendObj.addTask(backWebEngine.downloadModFromUrl(urlField.text), "addMod");
                                console.log("Add mod 2");
                                objModsList.refreshModlistVector();
                                qmlModsList.refreshModlist();
                            }
                        }
                    }

                    Layout.preferredWidth: navigationBar.height
                }

                Item { Layout.preferredWidth: 10 }

                ToolButton {
                    id: closeButton
                    text: qsTr(" X ")
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
    function openNewTab() {
        var newName = webView.contextMenuData.linkName
        var newUrl = webView.contextMenuData.linkUrl
        var element = {"name": newName ,"url": newUrl}
        qmlArticleView.openedSites.append(element)
    }
}
