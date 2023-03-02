#ifndef INFOBOX_H
#define INFOBOX_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "../../globaldata.h"

struct infoBoxData{
    infoBoxData() :
        cEnabled(false)
      , cContainButton(false)
      , x(0)
      , y(0)
      , cText("")
      , cButtonText("")
    {};
    bool cEnabled;
    bool cContainButton;
    uint64_t x;
    uint64_t y;
    QString cText;
    QString cButtonText;
};

class InfoBox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ getEnabled WRITE setEnabled NOTIFY changedEnabled)
    Q_PROPERTY(bool containButton READ getContainButton WRITE setContainButton NOTIFY containButtonEmit)
    Q_PROPERTY(QString infoText READ getText WRITE setText NOTIFY cTextEmit)
    Q_PROPERTY(QString buttonText READ getButtonText WRITE setButtonText NOTIFY cButtonTextEmit)
    Q_PROPERTY(int xPos READ getX WRITE setX NOTIFY xEmit)
    Q_PROPERTY(int yPos READ getY WRITE setY NOTIFY yEmit)

public:
    explicit InfoBox(QObject *parent = nullptr);

    void show();

public slots:
    bool getEnabled() const {return data.cEnabled; };
    void setEnabled(bool value){data.cEnabled = value; emit changedEnabled(); }

    bool getContainButton() const {return data.cContainButton; };
    void setContainButton(bool value){data.cContainButton = value; emit containButtonEmit(); }

    QString getText() const {return data.cText; }
    void setText(QString text) {data.cText = text; emit cTextEmit(); }

    QString getButtonText() const {return data.cButtonText; }
    void setButtonText(QString text) {data.cButtonText = text; emit cButtonTextEmit(); }

    int getX() const {return data.x; }
    void setX(int value) {data.x = value; emit xEmit(); }

    int getY() const {return data.y; }
    void setY(int value) {data.y = value; emit yEmit(); }

signals:
    void changedEnabled();
    void containButtonEmit();
    void xEmit();
    void yEmit();
    void cTextEmit();
    void cButtonTextEmit();

    void boxShown();

private:
    infoBoxData data;
};

#endif // INFOBOX_H
