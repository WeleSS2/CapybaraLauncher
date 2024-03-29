#include "githubupdater.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonarray.h"
#include "qnetworkreply.h"
#include "qeventloop.h"
#include "qfile.h"
#include "qcoreapplication.h"

GithubUpdater::GithubUpdater()
{

}

bool GithubUpdater::getVersionInfo(){
    menager = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://api.github.com/repos/WeleSS2/CapybaraLauncher/releases/latest"));

    reply = menager->get(request);

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject latestRelease = doc.object();
        QString latestVersion = latestRelease["name"].toString();

        QString currentVersion = QCoreApplication::applicationVersion();
        if (latestVersion == currentVersion) {
            qDebug() << "You are already running the latest version.";
            return false;
        } else {
            qDebug() << "A new version (" << latestVersion << ") is available. You should update. Current version: " + currentVersion;
            latestUrl = doc["assets"].toArray()[0].toObject()["browser_download_url"].toString();
            return true;
        }
    } else {
        qDebug() << "Error getting version information: " << reply->errorString();
        return false;
    }
}

void GithubUpdater::downloadPatch(){
    reply = menager->get(QNetworkRequest(QUrl(latestUrl)));

    QEventLoop loop;

    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void GithubUpdater::openPatchFile(){
    QFile file("temp_download.zip");
    if(file.open(QIODevice::WriteOnly)){
        file.write(reply->readAll());
        file.close();
    }
}

void GithubUpdater::patchAndResetApp() {
    QString path = QCoreApplication::applicationDirPath();

    std::string script = "start update.bat";

    int result = system(script.c_str());

    QCoreApplication::quit();
}
