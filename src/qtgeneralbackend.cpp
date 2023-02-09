#include "qtgeneralbackend.h"
#include "globaldata.h"
#include "qDebug.h"
#include "qguiapplication.h"
#include <cstdlib>
#include <filesystem>
#include <QClipboard>

QtGeneralBackend::QtGeneralBackend(QObject *parent)
    : QObject{parent}
{

}

void QtGeneralBackend::startGame()
{
    bool steamOn = SteamAPI_Init();
    std::string run = "";

    run += "start \"\" \"" + SharedGlobalDataObj->Global_LocalSettingsObj.gamepath
            + "\\steamapps\\common\\Total War WARHAMMER III\\Warhammer3.exe\"";

    for(auto& i: SharedGlobalDataObj->Global_ModsDataObj){
        if(i.done){
            run += "  add_working_directory  \"" +
                    SharedGlobalDataObj->Global_LocalSettingsObj.gamepath +
                    "\\steamapps\\workshop\\content\\1142710\\" +
                    std::to_string(i.steamModGameId) +
                    "\";" +
                    " mod \"" + i.steamPackname + "\";";
        }
    }

    qDebug() << QString::fromStdString(run);
    int result = system(run.c_str());
}

void QtGeneralBackend::exportPack(){
    std::string exportString = "";
    for(auto& i: SharedGlobalDataObj->Global_ModsDataObj){
        if(i.done){
            exportString += std::to_string(i.steamModGameId) + " ";
        }
    }
    QClipboard *clip = QGuiApplication::clipboard();
    clip->setText(QString::fromStdString(exportString));
}

void QtGeneralBackend::importPack(){

    QClipboard *clip = QGuiApplication::clipboard();

      // Create a string from the clipboard data
    std::string importList{QString(clip->text()).toStdString()};

      std::vector<uint32_t> mods;
      std::string number = "";
      qDebug() << QString::fromStdString(importList);
      for(int i = 0; i < importList.size(); ++i){
            number+= importList[i];
            qDebug() << QString::fromStdString(number) << "    " << importList[i];

            if(importList[i] == ' '){
                mods.emplace_back(std::stoul(number));
                number = "";
                qDebug() << QString::fromStdString(number) << "-----------";
            }
      }
      for(auto& i: SharedGlobalDataObj->Global_ModsDataObj)
      {
          for(int j = 0; j < mods.size() ; ++j){
              if(i.steamModGameId == mods[j])
              {
                  i.done = true;
              }
          }
      }
}

void QtGeneralBackend::removeModpack(QString name){
        std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.localPath +
                "\\Modpacks\\" + name.toStdString() + ".txt";
        if(std::filesystem::exists(path)){
            std::filesystem::remove(path);
        }
}
