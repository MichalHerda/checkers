import QtQuick 2.15
import QtQuick.Controls
import checkers.model
import Checkers 1.0

Rectangle {
    id: mainMenu
    anchors.fill: parent
    color: CheckersTheme.backgroundColor2
    property alias startGameButton: startGameButton

    Column {
        id: mainMenuColumn
        height: mainMenu.height
        width: mainMenu.width
        anchors.fill: parent

        Item {
            id: columnSeparator1
            height: mainMenuColumn.height * 0.05
            width: mainMenuColumn.width * 0.75
        }
/*
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
*/
        Image {
            id: mainMenuImage
            height: mainMenuColumn.height * 0.7
            width: mainMenuColumn.width * 0.9
            visible: true
            anchors.horizontalCenter: parent.horizontalCenter
            source: "/resources/Sepia-TonedCheckersGameIllustration.png"

        }

        Item {
            id: columnSeparator2
            height: mainMenuColumn.height * 0.05
            width: mainMenuColumn.width * 0.75
        }

        Row {
            id: buttonRow
            height: mainMenuColumn.height * 0.175
            width: mainMenuColumn.width

            Item {
                id: separatorLeft
                width: parent.width * 0.1
                height: parent.height * 0.5
            }

            Button {
                id: startGameButton
                width: parent.width * 0.35
                height: parent.height * 0.75
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter:  parent.verticalCenter
                text: "Start Game"
                font.family: "Cinzel Decorative"
                font.pixelSize: startGameButton.height * 0.5
                background: Rectangle {
                    color: CheckersTheme.buttonColor2
                    radius: 6
                    border.color: "#f5e9d4"
                }

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
                height: parent.height * 0.75
                //anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter:  parent.verticalCenter
                text: "Options"
                font.family: "Cinzel Decorative"
                font.pixelSize: optionsButton.height * 0.5
                background: Rectangle {
                    color: CheckersTheme.buttonColor2
                    radius: 6
                    border.color: "#f5e9d4"
                }
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
