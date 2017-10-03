import QtQuick 2.7
import FramelessWindowHelper 1.0
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3

Window {
    id: root
    width: 400;
    height: 300;
    color: "#6aacf1"
    visible: true;
    flags: Qt.WindowTitleHint
    title: ("caculator")
    FramelessWindowHelper{


    }

    Rectangle {
        id: titleBar
        height: 26
        color: "#32B17A"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Image {
            id: image
            x: 0
            y: 0
            width: 26
            height: 26
            source: "qrc:/res/dog.jpg"
        }

        Rectangle {
            id: closeBtn
            x: 360
            y: 0
            width: 40
            height: 26
            color: "#00ffffff"
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            MouseArea {
                id: mouseArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked:root.close()
                onEntered: {
                    closeBtn.color="#ff0000"
                    closeImg.source="qrc:/res/close-button2.png"
                }
                onExited: {
                    closeBtn.color="#00ffffff";
                    closeImg.source="qrc:/res/close-button1.png"
                }


            }

            Image {
                id: closeImg
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/res/close-button1.png"
            }
        }

        Rectangle {
            id: maxBtn
            width: 40
            height: 26
            color: "#00ffffff"
            anchors.right: closeBtn.left
            anchors.topMargin: 0
            anchors.top: parent.top
            anchors.rightMargin: 0
            MouseArea {
                id: mouseArea1
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    if(root.visibility==Window.FullScreen){
                        maxImg.source="qrc:/res/maximize-button1.png";
                        root.showNormal();
                    }else{
                        maxImg.source="qrc:/res/maximize-button2.png";
                        root.showFullScreen();
                    }
                }

                onEntered: maxBtn.color="#80c7c7c7"
                onExited: maxBtn.color="#00ffffff"
            }

            Image {
                id: maxImg
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/res/maximize-button1.png"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Rectangle {
            id: minBtn
            width: 40
            height: 26
            color: "#00ffffff"
            anchors.right: maxBtn.left
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            MouseArea {
                id: mouseArea2
                hoverEnabled: true
                anchors.fill: parent
                onEntered: minBtn.color="#80c7c7c7"
                onExited: minBtn.color="#00ffffff"
                onClicked: root.showMinimized()
            }
            Image {
                id: minImg
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:/res/minimize-button1.png"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        MouseArea {
            id: mouseArea3
            anchors.right: minBtn.left
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.rightMargin: 0
            property point pressPos
            onPressed: pressPos = Qt.point(mouse.x, mouse.y)
            onPositionChanged: {
                if (root.visibility == Window.Windowed) {
                    root.x += mouse.x - pressPos.x
                    root.y += mouse.y - pressPos.y
                }
            }
            onDoubleClicked:{
                if(root.visibility==Window.FullScreen){
                    maxImg.source="qrc:/res/maximize-button1.png";
                    root.showNormal();
                }else{
                    maxImg.source="qrc:/res/maximize-button2.png";
                    root.showFullScreen();
                }
            }

        }





    }

    GridLayout {
        id: gridLayout
        x: 156
        width: 244
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 96
        anchors.right: parent.right
        anchors.rightMargin: 0
    }

    TextEdit {
        id: textEdit
        text: qsTr("Text Edit")
        anchors.left: gridLayout.left
        anchors.leftMargin: 0
        anchors.bottom: gridLayout.top
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 52
        anchors.right: parent.right
        anchors.rightMargin: 0
        font.pixelSize: 12
    }



}
