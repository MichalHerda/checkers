import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0

Rectangle {
    id: root
    color: "black"
    radius: 6

    property alias restartGameButton: restartGameButton

    Column {
        id: endGameDialogColumn
        width: root.width
        height: root.height

        Item {
            id: separator1
            height: endGameDialogColumn.height * 0.05
        }

        Label {
            id: winnerLabel
            width: endGameDialogColumn.width * 0.75
            height: endGameDialogColumn.height * 0.45
            anchors.horizontalCenter: endGameDialogColumn.horizontalCenter
            horizontalAlignment: "AlignHCenter"
            verticalAlignment: "AlignVCenter"
            text: qsTr("GAME OVER !")
        }

        Item {
            id: separator2
            height: endGameDialogColumn.height * 0.05
        }

        Button {
            id: restartGameButton
            width: endGameDialogColumn.width * 0.75
            height: endGameDialogColumn.height * 0.4
            anchors.horizontalCenter: endGameDialogColumn.horizontalCenter
            background: Rectangle {
                anchors.fill: parent
                radius: 6
                color: CheckersTheme.buttonColor
                border.color: CheckersTheme.buttonBorderColor
            }

            Text {
                text: "Restart"
                color: CheckersTheme.fontColor
                anchors.centerIn: restartGameButton
                font {
                    pixelSize: restartGameButton * 0.5
                }
            }

            onClicked: {
                checkersGameBoard.emitReset()
            }
        }

        Item {
            id: separator3
            height: endGameDialogColumn.height * 0.05
        }
    }
}
