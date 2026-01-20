import QtQuick 2.15

Rectangle {
    id: piece
    property bool isKing: false
    property alias kingSign: kingSign
    radius: 180
    color: "black"
    border {
        color: "gold"
        width: !isKing ? piece.width * 0.025 : piece.width * 0.1
    }

    Rectangle {
        id: kingSign
        height: piece.height * 0.5
        width: height
        visible: isKing
        color: "black"
        radius: 180
        anchors.centerIn: parent
    }
}

