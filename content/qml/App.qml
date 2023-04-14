/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick Studio Components.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick.Window
import QtQuick.Controls

import content 1.0

Window {
    id: mainwindow
    width: Screen.width
    height: Screen.height

    visible: true
    visibility: Window.Maximized

    title: "Capybara Launcher"

    property string mainTextColor: "#E8E8E8"
    property string highlightTextColor:  "#D900D2E2"
    property bool modListEnabled: true
    property bool rightPanelEnabled: true
    property bool bottomGameMenuEnabled: true

    property string rectangleColor: "#FC070707"
    property string rectangleBorder: "#F9DFDFDF"

    Connections {
        target: localFilesObj
        function saveLocalSettings(){}
    }

    //Connections {
    //    target: objFilesOperations
    //    function saveSettings(){}
    //}

    property int width_1: mainwindow.width / 100
    property int height_1: mainwindow.height / 100
    property double baseScale: 1.0

    Image {
        id: background
        x: 0
        y: 0
        z: 0
        width: Window.width
        height: Window.height
        source: "../images/gameBackgrounds/background_0.png"
        fillMode: Image.Stretch
    }

    TopMenu {
        id: qmlTopMenu
        z: 0
    }

    GameSelector {
        id: qmlGameSelector
        z: 1
    }

    ModsListFile {
        id: qmlModsList
        visible: qmlGameSelector.currentGameId !== 0 ? true : false
        z: 0
    }

    RightPanel {
        id: qmlRightPanel
        visible: qmlGameSelector.currentGameId !== 0 ? true : false
        z: 0
    }

    BottomGameMenu
    {
        id: qmlBottomGameMenu
        visible: qmlGameSelector.currentGameId !== 0 ? true : false
        z: 0
    }

    ModListsOptions {
        id: qmlModListOptions
        visible: qmlGameSelector.currentGameId !== 0 ? true : false
        z: 0
    }

    TaskList
    {
        id: qmlTaskList
        z: 0
    }

    SettingsModule
    {
        id: qmlSettingsModule
        z: 0
    }

    InfoBox {
        id: infoBoxQML
        z: 0
    }

    ArticleView {
        id: qmlArticleView
        z: 2
    }

    Article {
        id: qmlArticle
        z: 2
    }

    onClosing: {
        console.log("Closing")
        localFilesObj.saveLocalSettings()
        //objFilesOperations.saveSettings()
        qtGeneralBackendObj.closeSteamAPIIfOn()
    }
}

