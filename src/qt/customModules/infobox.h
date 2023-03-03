#ifndef INFOBOX_H
#define INFOBOX_H

#include <QObject>
#include <QQmlContext>

class InfoBox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool boxStatus READ getBoxStatus WRITE setBoxStatus NOTIFY pingBox)
    Q_PROPERTY(bool containButton READ getButton WRITE setButton NOTIFY pingButton)
    Q_PROPERTY(int xPos READ getX WRITE setX NOTIFY pingX)
    Q_PROPERTY(int yPos READ getY WRITE setY NOTIFY pingY)
    Q_PROPERTY(QString boxText READ getBoxText WRITE setBoxText NOTIFY pingBoxText)
    Q_PROPERTY(QString buttonText READ getButtonText WRITE setButtonText NOTIFY pingButtonText)

public:
    explicit InfoBox(QObject* parent = nullptr);

    bool getBoxStatus() const {return boxStatus; };
    void setBoxStatus(bool _value){boxStatus = _value; emit pingBox(); };

    bool getButton() const {return containButton; };
    void setButton(bool _value) {containButton = _value; emit pingButton(); };

    uint64_t getX() const {return x; };
    void setX(uint64_t _value) {x = _value; emit pingX(); };

    uint64_t getY() const {return y; };
    void setY(uint64_t _value) {y = _value; emit pingY(); };

    QString getBoxText() const {return boxText; };
    void setBoxText(QString _value) {boxText = _value; emit pingBoxText(); };

    QString getButtonText() const {return buttonText; };
    void setButtonText(QString _value) {buttonText = _value; emit pingButtonText(); };
signals:
    void pingBox();
    void pingButton();
    void pingX();
    void pingY();
    void pingBoxText();
    void pingButtonText();

private:
    bool boxStatus = false;
    bool containButton = false;
    uint64_t x = 0;
    uint64_t y = 0;
    QString boxText = "";
    QString buttonText = "";
};

#endif // INFOBOX_H
