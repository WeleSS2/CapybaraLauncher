import QtQuick

Rectangle {
    id: overModList
    y: 100
    z: 0

    property alias enableCanvas : enableCanvas
    property alias nameCanvas : nameCanvas
    property alias dateCanvas : dateCanvas
    property alias packnameCanvas : packnameCanvas
    Text {
        width: 62
        height: 30
        x: 25
        text: qsTr("Enable")
        font.bold: true
        font.pixelSize: 16
        color: mainTextColor
        Canvas{
            id: enableCanvas
            width: 30
            height:30
            x: (parent.implicitWidth / 2) - 20
            y: -20

            property bool clicked: false

            onPaint:{
                 var context = getContext("2d");
                 context.reset();
                 // the triangle
                 context.beginPath();
                 context.moveTo(11, clicked ? 10 : 20);
                 context.lineTo(29, clicked ? 10 : 20);
                 context.lineTo(20, clicked ? 20 : 10);
                 context.closePath();


                 // the fill color
                 context.fillStyle = clicked ? "red" : "#FFCC00";
                 context.fill();
            }
            MouseArea {
                width: 50
                height: 50
                x: -10
                y: -10
                onClicked: (mouse)=>{
                               objModsList.sortByActive();
                               qmlModsList.refreshModlistTo0();
                               qmlModsList.onEnable();
                               clearCanvases();
                               parent.clicked = true;
                               parent.requestPaint();
                           }
            }
        }
    }

    Text {
        width: 108
        height: 30
        x: 190
        text: qsTr("Mod Name")
        font.bold: true
        font.pixelSize: 16
        color: mainTextColor
        Canvas{
            id: nameCanvas
            width: 30
            height:30
            x: (parent.implicitWidth / 2) - 20
            y: -20

            property bool clicked: false

            onPaint:{
                 var context = getContext("2d");
                 context.reset();
                 // the triangle
                 context.beginPath();
                 context.moveTo(11, clicked ? 10 : 20);
                 context.lineTo(29, clicked ? 10 : 20);
                 context.lineTo(20, clicked ? 20 : 10);
                 context.closePath();


                 // the fill color
                 context.fillStyle = clicked ? "red" : "#FFCC00";
                 context.fill();
            }
            MouseArea {
                width: 50
                height: 50
                x: -10
                y: -10
                onClicked: (mouse)=>{
                               objModsList.sortByName();
                               qmlModsList.refreshModlistTo0();
                               clearCanvases();
                               parent.clicked = true;
                               parent.requestPaint();
                           }
            }
        }
    }

    Text {
        x: 387
        width: 108
        height: 30
        color: mainTextColor
        text: qsTr("Update Date")
        font.pixelSize: 16
        font.bold: true
        Canvas{
            id: dateCanvas
            width: 30
            height:30
            x: (parent.implicitWidth / 2) - 20
            y: -20

            property bool clicked: false

            onPaint:{
                 var context = getContext("2d");
                 context.reset();
                 // the triangle
                 context.beginPath();
                 context.moveTo(11, clicked ? 10 : 20);
                 context.lineTo(29, clicked ? 10 : 20);
                 context.lineTo(20, clicked ? 20 : 10);
                 context.closePath();


                 // the fill color
                 context.fillStyle = clicked ? "red" : "#FFCC00";
                 context.fill();
            }
            MouseArea {
                width: 50
                height: 50
                x: -10
                y: -10
                onClicked: (mouse)=>{
                               objModsList.sortByDate();
                               qmlModsList.refreshModlistTo0();
                               clearCanvases();
                               parent.clicked = true;
                               parent.requestPaint();
                           }
            }
        }
    }

    Text {
        x: 610
        width: 108
        height: 30
        color: mainTextColor
        text: qsTr("Packname")
        font.pixelSize: 16
        font.bold: true
        Canvas{
            id: packnameCanvas
            width: 30
            height:30
            x: (parent.implicitWidth / 2) - 20
            y: -20

            property bool clicked: false

            onPaint:{
                 var context = getContext("2d");
                 context.reset();
                 // the triangle
                 context.beginPath();
                 context.moveTo(11, clicked ? 10 : 20);
                 context.lineTo(29, clicked ? 10 : 20);
                 context.lineTo(20, clicked ? 20 : 10);
                 context.closePath();


                 // the fill color
                 context.fillStyle = clicked ? "red" : "#FFCC00";
                 context.fill();
            }
            MouseArea {
                width: 50
                height: 50
                x: -10
                y: -10
                onClicked: (mouse)=>{
                               objModsList.sortByPackname();
                               qmlModsList.refreshModlistTo0();
                               clearCanvases();
                               parent.clicked = true;
                               parent.requestPaint();
                           }
            }
        }
    }

    Text {
        x: 860
        width: 108
        height: 30
        color: mainTextColor
        text: qsTr("Mod ID")
        font.pixelSize: 16
        font.bold: true
    }

    //Rectangle {
    //    id: refreshButton
    //    x: 980
    //    width: 30
    //    height: 30
    //    color: "transparent"
    //    MouseArea{
    //        anchors.fill: parent
    //        hoverEnabled: true
    //        onClicked: {
    //            if(Qt.LeftButton){
    //                objModsList.refreshModlistVector();
    //                refreshModlistTo0();
    //            }
    //        }
    //        onEntered: {
    //            refreshButtonImage.source = "images/icons/refreshIcon64Light.png"
    //        }
    //        onExited: {
    //            refreshButtonImage.source = "images/icons/refreshIcon64.png"
    //        }
    //    }
    //    Image {
    //        id: refreshButtonImage
    //        anchors.fill: parent
    //        source: "images/icons/refreshIcon64.png"
    //    }
    //}

    //Text {
    //    x: 977
    //    y: 100
    //    width: 108
    //    height: 30
    //    color: mainTextColor
    //    text: qsTr("Author")
    //    font.pixelSize: 16
    //    clip: true
    //    font.bold: true
    //}
    function clearCanvases(){
        enableCanvas.clicked = false;
        enableCanvas.requestPaint();
        nameCanvas.clicked = false;
        nameCanvas.requestPaint();
        dateCanvas.clicked = false;
        dateCanvas.requestPaint();
        packnameCanvas.clicked = false;
        packnameCanvas.requestPaint();
    }
}
