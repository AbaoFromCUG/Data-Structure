import QtQuick 2.0
import FramelessWindowHelper 1.0
import QtQuick.Window 2.3
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles.Breeze 1.0
import Caculator.abaopro.me 1.0
Window {
    id: root
    width: 400;
    height: 300;
    color: "#EEEEE0"
    visible: true;
    flags: Qt.WindowTitleHint
    title: ("caculator")
    minimumHeight: 300
    minimumWidth: 400
    FramelessWindowHelper{


    }
    Timer{
        id:clearTextTimer
        //Timer还提供了一些函数，如restart()、start()和stop()等
        interval: 1000; running:false; repeat:false
        onTriggered: showText.text=""
    }
    Caculator{
        id:cac
        onRunOver: {
            console.log(s,result)
             showText.text=result;
            if(s!=0){

                clearTextTimer.start()
            }else{
                //showText.text=cac.getShowText();
            }


        }



        function dealBtnClicked(s){

            cac.addDo(s)
            console.log(s);
            showText.text=cac.getShowText();
        }
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

    Rectangle {
        id: textEdit
        width: root.width>900?700:root.width*2/3
        anchors.top: titleBar.bottom
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5


        height: showText.height
        color: "#b0b0b0"
        radius: 5
        border.color: "#00000000"
        border.width: 3

        Text {
            id: showText
            text: qsTr("")
            font.bold: false
            width: parent.width
            color: "#ffffff"

            styleColor: "#e9d4d4"
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 20
        }
    }

    Flow {
        id: flow1
        spacing: 5
        anchors.leftMargin: 0
        anchors.top: textEdit.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: textEdit.left
        anchors.topMargin: 5

        Repeater{
            delegate:btn
            anchors.fill: parent

            model: ListModel{
                id:m_model
                /*
                 * 1    2   3
                  */
ListElement{m_text:"1"}ListElement{m_text:"2"}ListElement{m_text:"3"}ListElement{m_text:"UnDo"}ListElement{m_text:"Clear"}ListElement{m_text:"ReDo"}
ListElement{m_text:"4"}ListElement{m_text:"5"}ListElement{m_text:"6"}ListElement{m_text:"("}ListElement{m_text:"%"}ListElement{m_text:")"}
ListElement{m_text:"7"}ListElement{m_text:"8"}ListElement{m_text:"9"}ListElement{m_text:"sin"}ListElement{m_text:"cos"}ListElement{m_text:"tan"}
ListElement{m_text:"+"}ListElement{m_text:"0"}ListElement{m_text:"-"}ListElement{m_text:"^"}ListElement{m_text:"e"}ListElement{m_text:"√"}
ListElement{m_text:"x"}ListElement{m_text:"."}ListElement{m_text:"÷"}ListElement{m_text:"x²"}ListElement{m_text:"=";m_widthS:true}


            }
        }
    }

    Component{
        id:btn
        Button{
            property bool widthS:m_widthS;
            width: widthS?(flow1.width-30)/3+5:(flow1.width-30)/6
            height: (flow1.height-25)/5
            text:m_text
            onClicked:cac.dealBtnClicked(text)

            style: ButtonStyle{

                background: Rectangle{
                    border.width: 0
                    anchors.fill: parent
                    radius:  4

                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#B0E0E6" : "#87CEFA" }
                        GradientStop { position: 0.85 ; color: control.pressed ? "#B0E0E6" : "#87CEFA" }
                        GradientStop { position: 1 ; color: control.pressed ? "#B0E0E6" : "#BDBDBD" }
                    }
                }
            }


        }
    }






}
