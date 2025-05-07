import QtQuick 2.15
import QtQuick.Controls
import checkers.model

Rectangle {
    id: mainMenu
    anchors.fill: parent
    color: "black"
    property alias startGameButton: startGameButton

    Column {
        id: mainMenuColumn
        anchors.fill: parent

        Item {
            id: columnSeparator1
            height: mainMenuColumn.height * 0.15
            width: mainMenuColumn.width * 0.75
        }

        Rectangle {
            id: imageRectangle
            height: mainMenuColumn.height * 0.5
            width: mainMenuColumn.width * 0.75
            anchors.horizontalCenter: parent.horizontalCenter
            color: 'black'
            border {
                width: parent.width * 0.01
                color: 'blue'
            }

            Label {
                id: temporaryLabel
                text: "CHECKERS"
                font.pixelSize: parent.width * 0.15
                anchors.centerIn: imageRectangle
            }
        }

        Item {
            id: columnSeparator2
            height: mainMenuColumn.height * 0.05
            width: mainMenuColumn.width * 0.75
        }

        Row {
            id: buttonRow
            height: mainMenuColumn.height * 0.3
            width: mainMenuColumn.width

            Item {
                id: separatorLeft
                width: parent.width * 0.1
                height: parent.height * 0.5
            }

            Button {
                id: startGameButton
                width: parent.width * 0.35
                height: parent.height * 0.5
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter:  parent.verticalCenter
                text: "START GAME"
                onClicked: {
                    //root.isMainMenu === true
                    root.isMainMenu = !root.isMainMenu
                    checkersModelInstance.gameOn = true;
                    checkersModelInstance.player = CheckersModel.Player.white
                }
            }

            Item {
                id: separatorMiddle
                width: parent.width * 0.1
                height: parent.height * 0.5
            }

            Button {
                id: optionsButton
                width: parent.width * 0.35
                height: parent.height * 0.5
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter:  parent.verticalCenter
                text: "OPTIONS"
                onClicked: {
                    console.log("options button clicked")
                }
            }

            Item {
                id: separatorRight
                width: parent.width * 0.1
                height: parent.height * 0.5
            }
        }
    }
}
