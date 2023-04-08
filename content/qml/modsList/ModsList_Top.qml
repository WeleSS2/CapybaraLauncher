import QtQuick

Rectangle {
    id: overModList
    y: 100

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
            property bool hovered: false

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
                 context.fillStyle = clicked  || hovered ? "green" : "#FFCC00";
                 context.fill();
            }
            MouseArea {
                width: 50
                height: 50
                x: -10
                y: -10
                hoverEnabled: true
                onClicked: (mouse)=>{
                               objModsList.sortByActive();
                               qmlModsList.refreshModlistTo0();
                               qmlModsList.onEnable();
                               clearCanvases();
                               parent.clicked = true;
                               parent.requestPaint();
                           }
                onHoveredChanged: (mouse)=>{
                                      if(containsMouse){
                                          qmlGameSelector.z = 0;
                                          parent.hovered = true;
                                          parent.requestPaint();
                                      }
                                      else
                                      {
                                          qmlGameSelector.z = 1;
                                          parent.hovered = false;
                                          parent.requestPaint();
                                      }
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
            property bool hovered: false

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
                 context.fillStyle = clicked  || hovered ? "green" : "#FFCC00";
                 context.fill();
            }
            MouseArea {
                width: 50
                height: 50
                x: -10
                y: -10
                hoverEnabled: true
                onClicked: (mouse)=>{
                               objModsList.sortByName();
                               qmlModsList.refreshModlistTo0();
                               clearCanvases();
                               parent.clicked = true;
                               parent.requestPaint();
                           }
                onHoveredChanged: (mouse)=>{
                                      if(containsMouse){
                                          qmlGameSelector.z = 0;
                                          parent.hovered = true;
                                          parent.requestPaint();
                                      }
                                      else
                                      {
                                          qmlGameSelector.z = 1;
                                          parent.hovered = false;
                                          parent.requestPaint();
                                      }
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
            property bool hovered: false

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
                 context.fillStyle = clicked  || hovered ? "green" : "#FFCC00";
                 context.fill();
            }
            MouseArea {
                width: 50
                height: 50
                x: -10
                y: -10
                hoverEnabled: true
                onClicked: (mouse)=>{
                               objModsList.sortByDate();
                               qmlModsList.refreshModlistTo0();
                               clearCanvases();
                               parent.clicked = true;
                               parent.requestPaint();
                           }
                onHoveredChanged: (mouse)=>{
                                      if(containsMouse){
                                          qmlGameSelector.z = 0;
                                          parent.hovered = true;
                                          parent.requestPaint();
                                      }
                                      else
                                      {
                                          qmlGameSelector.z = 1;
                                          parent.hovered = false;
                                          parent.requestPaint();
                                      }
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
            property bool hovered: false

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
                 context.fillStyle = clicked  || hovered ? "green" : "#FFCC00";
                 context.fill();
            }
            MouseArea {
                width: 50
                height: 50
                x: -10
                y: -10
                hoverEnabled: true
                onClicked: (mouse)=>{
                               objModsList.sortByPackname();
                               qmlModsList.refreshModlistTo0();
                               clearCanvases();
                               parent.clicked = true;
                               parent.requestPaint();
                           }
                onHoveredChanged: (mouse)=>{
                                      if(containsMouse){
                                          qmlGameSelector.z = 0;
                                          parent.hovered = true;
                                          parent.requestPaint();
                                      }
                                      else
                                      {
                                          qmlGameSelector.z = 1;
                                          parent.hovered = false;
                                          parent.requestPaint();
                                      }
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
