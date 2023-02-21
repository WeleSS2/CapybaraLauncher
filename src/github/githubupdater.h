#pragma once
#include "QNetworkAccessManager"

class GithubUpdater
{
public:
    GithubUpdater();
    void getVersionInfo();
    void downloadPatch();
    void openPatchFile();
    void patchAndResetApp();
private:
    QNetworkAccessManager *menager;
    QNetworkReply *reply;
};
