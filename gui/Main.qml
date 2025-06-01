import QtQuick
import QtQuick.Controls
import Checkers 1.0
import checkers.model

import "frontEnd.js" as Js

Window {
    id: root
    width: 800
    height: 600
    visible: true
    title: qsTr("Checkers")
    color: CheckersTheme.backgroundColor

    property bool isMainMenu: true
    property bool isOptionsMenu: false
    property bool rotateGameBoard: false
    property bool completed: false

    property double buttonWidth: root.width * 0.28
    property double buttonHeight: root.height * 0.075
    property double buttonsSeparatorX: root.width * 0.04

    property string playerOneName: "Player 1"
    property string playerTwoName: "Player 2"

    property int widthStash: 800
    property int heightStash: 600

    property bool isMaximized: false

    Item {
        id: anchorItem
        anchors.fill: parent

        Menu {
            visible: isMainMenu
        }

        Options {
            width: parent.width * 0.95
            height: parent.height * 0.95
            visible: isOptionsMenu
            anchors.centerIn: parent
        }

        PlayerTimersRow {
            id: playerTimersRow

            width: anchorItem.width * 0.9
            height: anchorItem.height * 0.1
            anchors.horizontalCenter: anchorItem.horizontalCenter
            visible: !isMainMenu
            y: parent.height * 0.025
        }

        GameBoard {
            id: checkersGameBoard
            property double fieldWidth:  checkersGameBoard.width / checkersModelInstance.getColumnsNo()
            property double fieldHeight:  checkersGameBoard.height / checkersModelInstance.getRowsNo()
            property double pieceWidth: fieldWidth * CheckersTheme.pieceDimensionModificator
            property double pieceHeight: fieldHeight * CheckersTheme.pieceDimensionModificator
            property double pieceSeparatorX: (fieldWidth - pieceWidth) / 2
            property double pieceSeparatorY: (fieldHeight - pieceHeight) / 2

            anchors.centerIn: parent
            width: root.width * 0.5
            height: root.height * 0.675
            transformOrigin: Item.Center
            rotation: rotateGameBoard ? 180 : 0
            visible: !isMainMenu
        }

        Button {
            id: testButton
            width: buttonWidth
            height: buttonHeight
            x: buttonsSeparatorX
            y: parent.height - ( parent.height * 0.125 )
            visible: !isMainMenu

            background: Rectangle {
                anchors.fill: parent
                radius: 6
                color: CheckersTheme.buttonColor
                border.color: CheckersTheme.buttonBorderColor
            }

            Text {
                text: "Test Button"
                color: CheckersTheme.fontColor
                anchors.centerIn: parent
                font {
                    family: "Cinzel Decorative"
                    pixelSize: buttonHeight * 0.5
                }
            }

            onClicked: {
                checkersModelInstance.printModel()
            }
        }

        Button {
            id: rotateButton
            width: buttonWidth
            height: buttonHeight        
            x: ( buttonsSeparatorX * 2 ) + buttonWidth
            y: parent.height - ( parent.height * 0.125 )
            visible: !isMainMenu

            background: Rectangle {
                anchors.fill: parent
                radius: 6
                color: CheckersTheme.buttonColor
                border.color: CheckersTheme.buttonBorderColor
            }

            Text {
                text: "Rotate"
                color: CheckersTheme.fontColor
                anchors.centerIn: parent
                font {
                    family: "Cinzel Decorative"
                    pixelSize: buttonHeight * 0.5
                }
            }

            onClicked: {
                root.rotateGameBoard = !root.rotateGameBoard
                console.log("rotateGameBoard: ", rotateGameBoard)
            }
        }

        Button {
            id: restartButton
            width: buttonWidth
            height: buttonHeight
            x: ( buttonsSeparatorX * 3 ) + ( buttonWidth * 2 )
            y: parent.height - ( parent.height * 0.125 )
            visible: !isMainMenu

            property var fieldRep: checkersGameBoard.fieldRep
            property var pieceRep: checkersGameBoard.pieceRep

            property double fieldWidth:  checkersGameBoard.width / checkersModelInstance.getColumnsNo()
            property double fieldHeight:  checkersGameBoard.height / checkersModelInstance.getRowsNo()
            property double pieceWidth: fieldWidth * CheckersTheme.pieceDimensionModificator
            property double pieceHeight: fieldHeight * CheckersTheme.pieceDimensionModificator
            property double pieceSeparatorX: (fieldWidth - pieceWidth) / 2
            property double pieceSeparatorY: (fieldHeight - pieceHeight) / 2


            background: Rectangle {
                anchors.fill: parent
                radius: 6
                color: CheckersTheme.buttonColor
                border.color: CheckersTheme.buttonBorderColor
            }

            Text {
                text: "Restart"
                color: CheckersTheme.fontColor
                anchors.centerIn: parent
                font {
                    family: "Cinzel Decorative"
                    pixelSize: buttonHeight * 0.5
                }
            }

            onClicked: {
                checkersGameBoard.emitReset()
            }
        }
    }

    Timer {
        id: debugTimer
        interval: 5000
        repeat: true
        running: true
        onTriggered: {
            //console.log("gameSettingsManager.gameMode: ", gameSettingsManager.gameMode)
            //console.log("gameSettingsManager.gameTime: ", gameSettingsManager.gameTime)
            //console.log("checkersModelInstance.player: ", checkersModelInstance.player)
            //console.log("checkersModelInstance.gameon: ", checkersModelInstance.gameOn)
            //console.log("must capture, player", checkersModelInstance.player, ": ", checkersModelInstance.mustCapture(checkersModelInstance.player))
        }
    }

    onVisibilityChanged: {
        console.log("Zmieniono visibility:")
        widthStash = root.width
        heightStash = root.height
        if(visibility === Window.Maximized) {
            console.log("maximized")
            if(!isMaximized) {
                console.log("!isMaximized, widthStash: ", widthStash, ", heightStash: ", heightStash)
                widthStash = root.width
                heightStash = root.height
                root.width = screen.width
                root.height = screen.height
                isMaximized = true
            }

            else {
                //console.log("!isMinimized, widthStash: ", widthStash, ", heightStash: ", heightStash)
                root.width = widthStash
                root.height = heightStash
                isMaximized = false
                //checkersGameBoard.handleVisibilityChanged()
            }

        }
        checkersGameBoard.handleVisibilityChanged()
    }
}
