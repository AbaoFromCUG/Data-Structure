import QtQuick 2.0

Item {

    width: 500
    height: 500

    Rectangle {
        id: rectangle
        x: 88
        y: 81
        width: 300

        height: showText.height
        color: "#b0b0b0"
        radius: 5
        border.color: "#00000000"
        border.width: 3

        Text {
            id: showText
            text: qsTr("1+2*23423434+344fasdfdfdsf+3345344354-343232245414654")
            font.bold: false
            width: parent.width
            color: "#ffffff"

            styleColor: "#e9d4d4"
            wrapMode: Text.WrapAnywhere
            font.pixelSize: 50
        }
    }

}
