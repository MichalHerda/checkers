import QtQuick 2.15

Rectangle {
    id: piece
    //anchors.centerIn: parent
    height: parent.height * 0.7
    width: height
    radius: 180
    color: "black"
    border {
        color: "gold"
        width: piece.width * 0.025
    }
}

