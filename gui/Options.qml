import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0

Rectangle {
    id: optionsMenu
    color: CheckersTheme.backgroundColor2

    Row {
        id: optionsButtondRow
        width: parent.width
        height: parent.height * 0.2
        anchors.bottom: parent.bottom

        Item {
            id: separatorLeft
            width: parent.width * 0.1
            height: parent.height * 0.5
        }

        Button {
            id: writeAndCloseButton
            width: parent.width * 0.35
            height: parent.height * 0.75
            anchors.verticalCenter:  parent.verticalCenter
            onClicked: {
                root.isOptionsMenu = false;
            }

            Text {
                text: "Write And Close"
                color: CheckersTheme.fontColor
                anchors.centerIn: parent
                font {
                    family: "Cinzel Decorative"
                    pixelSize: writeAndCloseButton.height * 0.3
                }
            }
        }

        Item {
            id: separatorMiddle
            width: parent.width * 0.1
            height: parent.height * 0.5
        }

        Button {
            id: closeButton
            width: parent.width * 0.35
            height: parent.height * 0.75
            anchors.verticalCenter:  parent.verticalCenter
            onClicked: {
                root.isOptionsMenu = false;
            }

            Text {
                text: "Close"
                color: CheckersTheme.fontColor
                anchors.centerIn: parent
                font {
                    family: "Cinzel Decorative"
                    pixelSize: closeButton.height * 0.5
                }
            }
        }

        Item {
            id: separatorRight
            width: parent.width * 0.1
            height: parent.height * 0.5
        }
    }
}
