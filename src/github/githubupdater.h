#pragma once
#include "QNetworkAccessManager"

class GithubUpdater
{
public:
    GithubUpdater();
    bool getVersionInfo();
    void downloadPatch();
    void openPatchFile();
    void patchAndResetApp();
private:
    QNetworkAccessManager *menager;
    QNetworkReply *reply;
    QString latestUrl;
};
