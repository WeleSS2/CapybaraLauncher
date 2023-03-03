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
 * 2. Napraw ustawienia po usunieciu zeby sie odtwarzaly
 * 3. Napraw nadpisywnie listy modow, aktualnie nie nadpisuje sie +
 *
 *
 * Patch 0.0.4 + fixes ^ Until 01.03
 * - Popup/Infobox for downlading update and mods by import +
 * - Open mod locally +
 * -
 * ------------------------- FINISHED 03.03.2023 22:30
 * Patch 0.0.5 Until 05.03
 * - Custom server layer
 * - Add news in right panel
 *
 *
 * Closed public alpha
 *
 * Patch 0.0.6 Until 07.03
 * - Game menagement
 * - Update game/mods
 * - Crashifier, check did game is running if crashed disable half of the mods and check until game is not running correctly.
 *
 *
 * Patch 0.0.7 Until 12.03
 * - Web layer
 *
 *
 * Patch 0.0.8 Until 15.03
 * - Neccesary add-ons and fixes
 * - Idk what exactly, to be added
 *
 * Open Alpha Relase
 *
 * Patch 0.1.1
 * - Reworking code, multigame support alpha version
 *
 */
#include <QGuiApplication>

#include <QObject>
#include <QQmlContext>
#include <QQmlProperty>

#include "app_environment.h"
#include "import_qml_plugins.h"
#include "steam_api.h"

#include "github/githubupdater.h"
#include "localfiles.h"
#include "globaldata.h"
#include "exit.h"
#include "cmodslistfile.h"
#include "cmodslistfilling.h"
#include "modpackslist.h"
#include "qtgeneralbackend.h"
#include "qt/customModules/infobox.h""

class steam
{
public:
    steam()
    {
        if(SteamAPI_Init())
        {
            CSteamTools steamOperations;
            SharedSteamToolsObj->LoadItemsToQuery();
            SharedSteamToolsObj->LoadItemsDataFromQuery();
            std::cout << "SteamAPI Loaded" << std::endl;
        }
    };
};


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

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    SharedGlobalDataObj->enginePtr = &engine;

    QCoreApplication::setApplicationVersion("v0.0.3.4");

    cexit exit_obj;
    engine.rootContext()->setContextProperty("exit_obj", &exit_obj);


    localFiles localFilesObj;
    engine.rootContext()->setContextProperty("localFilesObj", &localFilesObj);

    settingsLoading();
    {
        steam runSteam;
    }

    QtGeneralBackend qtGeneralBackendObj;
    engine.rootContext()->setContextProperty("qtGeneralBackendObj", &qtGeneralBackendObj);

    qmlRegisterType<CModsListFile>("CModsList", 1, 0, "CModsListFile");
    qmlRegisterUncreatableType<cmodslistfilling>("CModsList", 1, 0, "Cmodslistfilling", QString("Sometthing"));

    cmodslistfilling Objcmodslistfilling;
    engine.rootContext()->setContextProperty("Objcmodslistfilling", &Objcmodslistfilling);

    qmlRegisterType<ModpacksList>("ModPacksList", 1, 0, "ModpacksList");
    qmlRegisterUncreatableType<ModpacksContent>("ModPacksList", 1, 0, "ModpacksContent", QString("Sometthing"));

    ModpacksContent ObjModpacksContent;
    engine.rootContext()->setContextProperty("ObjModpacksContent", &ObjModpacksContent);

    InfoBox ObjInfoBox;
    engine.rootContext()->setContextProperty("ObjInfoBox", &ObjInfoBox);


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
