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
/* TODO:
 *
 *
 *
 * Patch 0.0.4 + fixes ^ Until 01.03
 * - Popup/Infobox for downlading update and mods by import +
 * - Open mod locally +
 * -
 * ------------------------- FINISHED 03.03.2023 22:30
 *
 *
 * Patch 0.0.5 Until 07.03
 * - Local mods support +
 * - Add mods to steam support - / Impossible to do as i think...
 * - Multigame support Alpha +
 *
 * ---------------------------- FINISHED 08.03.2023 12:55 also not worked
 * - Last changelog for mod (hiperlink) - For what? Not needed
 * - Change mod color if not updated and add option to update mod +
 * - Make copy of steam mod as local mod +
 * - Option to remove local mods +
 * - Open mod with rpfm +
 * - Make new local mod +
 * - Fix start for every game +
 *
 *
 *
 * ----------------------------- FINISHED 16.03.2023 + fixes for multigame support...
 *
 *
 *
 * Patch 0.0.6 Until 20.03
 * - Add background for every game +
 * - Fix settings menu issues +
 * - Custom menu background +
 *
 *-------------- FINISHED 19.03
 *
 *  Patch 0.0.7 Until 25.03
 * - Web layer +
 * - Remove consoles from view +
 * - Custom server layer +
 * - Add news in right panel +
 * - Game menagement (What i wanted to do here? Do not remember just) -
 * - Update mods +
 *
 *
 *--------------- FINISHED 28.03
 * Patch 0.0.8 Until 30.03
 * - Neccesary add-ons and fixes
 * - Idk what exactly, to be added
 * - Worskapces/Backups for local mods
 * - Update game
 * - Option, enable steam if not running
 * - Crashifier, check did game is running if crashed disable half of the mods and check until game is not running correctly. (Later better version, delayed) -
 * - Better update system, keep .zip in file and download only zip files from github which have been changed
 *
 * Open Beta Relase
 * - Remove GlobalData.cpp and translate everything into correct object-oriented app
 * - Remove qtgeneralbackend.cpp and move correctly.
 *
 *
 *
 *
 * TODO:
 * LOG01 - IMPLEMENTATION FOR LOGS, find later and fill
 */

// Qt neccesary
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick/QtWebEngineQuick>
#include <QtWebView>


#include <QObject>
#include <QQmlContext>
#include <QQmlProperty>

#include "app_environment.h"

// Other files



// Other custom files
#include "qtgeneralbackend.h"
#include "utility/loggingsystem.h"
#include "localfiles/localfiles.h"
#include "system/windowsfunctions.h"
#include "qt/customModules/gamechanger.h"
#include "qt/customModules/modslistfile.h"
#include "qt/customModules/modpackslist.h"
#include "qt/customModules/infobox.h"
#include "qt/customModules/news.h"

void settingsLoading()
{
    localFiles temp;
    if(temp.findLocalFolder())
    {
        std::string settingsPath = temp.localWh3Path + "\\settings.txt";
        if(temp.findLocalDataTxt(settingsPath))
        {
            temp.loadLocalSettings();
        }
    }
}

int main(int argc, char *argv[])
{
    set_qt_environment();
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QGuiApplication app(argc, argv);
    FreeConsole();
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);



    QQmlApplicationEngine engine;
    GlobalDataObj->enginePtr = &engine;

    QCoreApplication::setApplicationVersion("v0.0.7.1");

    // WORKSPACE
    // settings are doubled due to work over transfer to .js
    // DO NOT WORK
    //
    //FilesOperations objFilesOperations;
    //objFilesOperations.loadSettings(); // Not working now
    //engine.rootContext()->setContextProperty("objFilesOperations", &objFilesOperations);
    //
    // -DO NOT WORK


    localFiles localFilesObj;
    engine.rootContext()->setContextProperty("localFilesObj", &localFilesObj);

    // Temporary must be fired always (And i think will stay like that permamently)
    WindowsFunctions winFun;
    winFun.getSteamPathFromRegistry();

    settingsLoading();

    LoggingSystem::clearLogs();

    //--------------------------------------------
    //            Load default game
    //--------------------------------------------

    if(GlobalDataObj->LocalSettingsObj.currentGame.gameId > 0){
        GameChanger obj;
        obj.setCurrentGame(1000);
    }


    //---------------------------------------------
    //                 GameChanger
    //---------------------------------------------

    qmlRegisterType<GameChanger>("cGameChangerListUrl", 1, 0, "GameChanger");
    qmlRegisterUncreatableType<cGameChangerList>("cGameChangerListUrl", 1, 0, "GameChangerList", QString("I dont have any reason"));

    cGameChangerList objcGameChangerList;
    engine.rootContext()->setContextProperty("ObjcGameChangerList", &objcGameChangerList);

    //---------------------------------------------
    //                  ModsList
    //---------------------------------------------

    qmlRegisterType<Mods>("cMods", 1, 0, "Mods");
    qmlRegisterUncreatableType<ModsList>("cMods", 1, 0, "ModsList", QString("Sometthing"));

    ModsList objModsList;
    engine.rootContext()->setContextProperty("objModsList", &objModsList);

    //--------------------------------------------
    //               Local Modpacks
    //--------------------------------------------

    qmlRegisterType<ModpacksList>("ModPacksList", 1, 0, "ModpacksList");
    qmlRegisterUncreatableType<ModpacksContent>("ModPacksList", 1, 0, "ModpacksContent", QString("Sometthing"));

    ModpacksContent ObjModpacksContent;
    engine.rootContext()->setContextProperty("ObjModpacksContent", &ObjModpacksContent);

    //--------------------------------------------
    //                News module
    //--------------------------------------------

    qmlRegisterType<News>("cNews", 1, 0, "News");
    qmlRegisterUncreatableType<News>("cNews", 1, 0, "DevNewsList", QString("Smth"));
    qmlRegisterUncreatableType<News>("cNewsList", 1, 0, "CommunityNewsList", QString("Smth"));

    DevNewsList cDevNewsList;
    engine.rootContext()->setContextProperty("cDevNewsList", &cDevNewsList);

    CommunityNewsList cCommunityNewsList;
    engine.rootContext()->setContextProperty("cCommunityNewsList", &cCommunityNewsList);

    //--------------------------------------------
    //              QtGeneralBackend
    //--------------------------------------------

    QtGeneralBackend qtGeneralBackendObj;
    engine.rootContext()->setContextProperty("qtGeneralBackendObj", &qtGeneralBackendObj);

    //--------------------------------------------
    //                  InfoBox
    //--------------------------------------------

    InfoBox ObjInfoBox;
    engine.rootContext()->setContextProperty("ObjInfoBox", &ObjInfoBox);

    //--------------------------------------------
    //            Load default game
    //--------------------------------------------

    if(GlobalDataObj->LocalSettingsObj.currentGame.gameId > 0){
        ObjModpacksContent.modlistAmount();
    }


    //------------------------------------------------------------
    //
    //                       Connections
    //
    //------------------------------------------------------------

    QObject::connect(&app, &QGuiApplication::applicationStateChanged,
                         [&](Qt::ApplicationState state) {
            if (state == Qt::ApplicationActive) {
                QtWebEngineQuick::initialize();
                QtWebView::initialize();
            }
        });

    const QUrl url(u"qrc:Main/main.qml"_qs);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);


    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);


    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
