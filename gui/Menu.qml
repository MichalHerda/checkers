import QtQuick 2.15
import QtQuick.Controls
import checkers.model
import Checkers 1.0

Rectangle {
    id: mainMenu
    anchors.fill: parent
    color: CheckersTheme.backgroundColor
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

        Image {
            id: mainMenuImage
            height: mainMenuColumn.height * 0.8
            width: mainMenuColumn.width * 0.9
            visible: true
            anchors.horizontalCenter: parent.horizontalCenter
            source: "/resources/Sepia-TonedCheckersGameIllustration.png"
        }

        Item {
            id: columnSeparator2
            height: mainMenuColumn.height * 0.025
            width: mainMenuColumn.width * 0.75
        }

        Row {
            id: buttonRow
            height: mainMenuColumn.height * 0.1
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
                anchors.verticalCenter:  parent.verticalCenter
                background: Rectangle {
                    color: CheckersTheme.buttonColor
                    radius: 6
                    border.color: CheckersTheme.buttonBorderColor
                }

                Text {
                    text: "Start Game"
                    color: CheckersTheme.fontColor
                    anchors.centerIn: parent
                    font {
                        family: "Cinzel Decorative"
                        pixelSize: startGameButton.height * 0.5
                    }
                }

                onClicked: {
                    root.isMainMenu = !root.isMainMenu
                    GameController.gameOn = true;
                    GameController.player = CheckersModel.Player.white
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
                anchors.verticalCenter:  parent.verticalCenter
                background: Rectangle {
                    color: CheckersTheme.buttonColor
                    radius: 6
                    border.color: CheckersTheme.buttonBorderColor
                }

                Text {
                    text: "Options"
                    color: CheckersTheme.fontColor
                    anchors.centerIn: parent
                    font {
                        family: "Cinzel Decorative"
                        pixelSize: startGameButton.height * 0.5
                    }
                }

                onClicked: {
                    root.isOptionsMenu = !root.isOptionsMenu
                    console.log("options button clicked, root.isOptionsMenu: ", root.isOptionsMenu )
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
