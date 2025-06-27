import QtQuick 2.15
import QtQuick.Controls

Rectangle {
    id: root
    color: "black"

    Label {
        id: winnerLabel
        width: root.width * 0.75
        height: root.height * 0.9
        anchors.centerIn: parent
        horizontalAlignment: "AlignHCenter"
        verticalAlignment: "AlignVCenter"
        text: qsTr("GAME OVER!")
    }
}
