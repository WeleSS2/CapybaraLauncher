#include "githubupdater.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonarray.h"
#include "qnetworkreply.h"
#include "qeventloop.h"
#include "qfile.h"
#include "qprocess.h"
#include "qcoreapplication.h"

GithubUpdater::GithubUpdater()
{

}

void GithubUpdater::getVersionInfo(){
    menager = new QNetworkAccessManager();
    QNetworkRequest request(QUrl("https://api.github.com/repos/WeleSS2/WH3_Mod_Menager/releases/latest"));

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
        } else {
            qDebug() << "A new version (" << latestVersion << ") is available. You should update.";
            //downloadPatch();
        }
    } else {
        qDebug() << "Error getting version information: " << reply->errorString();
    }
}

void GithubUpdater::downloadPatch(){
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject latestRelease = doc.object();
    QString downloadUrl = latestRelease["assets"].toArray()[0].toObject()["browser_download_url"].toString();

    reply = menager->get(QNetworkRequest(QUrl(downloadUrl)));

    QEventLoop loop;

    QAbstractSocket::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    openPatchFile();
}

void GithubUpdater::openPatchFile(){
    QFile file("temp_download.zip");
    if(file.open(QIODevice::WriteOnly)){
        file.write(reply->readAll());
        file.close();
    }
    patchAndResetApp();
}

void GithubUpdater::patchAndResetApp(){
    QString path = QCoreApplication::applicationDirPath();
    QProcess process;
    process.start("unzip -o temp_download.zip -d " + path);
    process.waitForFinished();

    QCoreApplication::quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
