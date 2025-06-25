import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0
import GameSettingsManager 1.0
import checkers.model
import game.settings
import "frontEnd.js" as Js

Rectangle {
    id: optionsMenu
    color: CheckersTheme.backgroundColor

    Column {
        id: optionsColumn
        width: parent.width * 0.8
        height: parent.height * 0.7
        anchors.top: parent.top

        Row {
            id: gameModeRow
            width: parent.width
            height: parent.height * 0.2
            anchors.horizontalCenter: parent.horizontalCenter

            Label {
                id: gameModeLabel
                width: gameModeRow.width * 0.5
                height: gameModeRow.height * 0.9
                text: "Game Mode: "
            }

            ComboBox {
                id: gameModeComboBox
                width: gameModeRow.width * 0.5
                height: gameModeRow.height * 0.9

                property bool initializing: true

                model: [
                        { text: "Human vs Computer", value: GameSettingsManager.GameMode.humanVsComputer},
                        { text: "Human vs Human (Hot Seat)", value: GameSettingsManager.GameMode.humanVsHumanHotSeat },
                        { text: "Human vs Human (Online)", value: GameSettingsManager.GameMode.humanVsHumanOnline }
                ]
                textRole: "text"
                valueRole: "value"

                onCurrentIndexChanged: {
                    if(!initializing) {
                        gameSettingsManager.gameMode = model[currentIndex].value;
                    }
                }

                Component.onCompleted: {
                     for (var i = 0; i < model.length; i++) {
                           if (model[i].value === gameSettingsManager.gameMode)
                               currentIndex = i;
                               //console.log("current index ", currentIndex)
                     }
                     initializing = false;
                }
            }
        }


        Row {
            id: gameTimeRow
            width: parent.width
            height: parent.height * 0.2
            anchors.horizontalCenter: parent.horizontalCenter

            Label {
                id: gameTimeLabel
                width: gameTimeRow.width * 0.5
                height: gameTimeRow.height * 0.9
                text: "Game Time: "
            }

            ComboBox {
                id: gameTimeComboBox
                width: gameTimeRow.width * 0.5
                height: gameTimeRow.height * 0.9

                property bool initializing: true

                model: [
                        {text: "1 minute", value: GameSettingsManager.GameTime.minute1},
                        {text: "2 minutes", value: GameSettingsManager.GameTime.minutes2},
                        {text: "5 minutes", value: GameSettingsManager.GameTime.minutes5},
                        {text: "10 minutes", value: GameSettingsManager.GameTime.minutes10},
                        {text: "15 minutes", value: GameSettingsManager.GameTime.minutes15},
                        {text: "20 minutes", value: GameSettingsManager.GameTime.minutes20},
                        {text: "30 minutes", value: GameSettingsManager.GameTime.minutes30},
                        {text: "no time limit", value: GameSettingsManager.GameTime.nolimit}
                    ]
                textRole: "text"
                valueRole: "value"

                onCurrentIndexChanged: {
                    if(!initializing) {
                        gameSettingsManager.gameTime = model[currentIndex].value;
                    }
                }

                Component.onCompleted: {
                     for (var i = 0; i < model.length; i++) {
                           if (model[i].value === gameSettingsManager.gameTime)
                               currentIndex = i;
                               //console.log("current index ", currentIndex)
                     }
                     initializing = false;
                }
            }
        }

        Row {
            id: gameStyleRow
            width: parent.width
            height: parent.height * 0.2
            anchors.horizontalCenter: parent.horizontalCenter

            Label {
                id: gameStyleLabel
                width: gameStyleRow.width * 0.5
                height: gameStyleRow.height * 0.9
                text: "Game Style: "
            }
        /*
            ComboBox {
                id: gameStyleComboBox
                width: gameModeRow.width * 0.5
                height: gameModeRow.height * 0.9
                model: ["dark", "cosmic", "fantasy", "brony"]

                onCurrentIndexChanged: {
                    if(currentIndex == 0) {
                        console.log("dark")
                        CheckersTheme.backgroundColor = CheckersTheme.backgroundColor2
                        CheckersTheme.buttonColor = CheckersTheme.buttonColor2
                        CheckersTheme.buttonBorderColor = CheckersTheme.buttonBorderColor2
                        CheckersTheme.fontColor = CheckersTheme.fontColor2
                        CheckersTheme.playableFieldColor = CheckersTheme.playableFieldColor2
                        CheckersTheme.notPlayableFieldColor = CheckersTheme.notPlayableFieldColor2
                        CheckersTheme.fieldBorderColor = CheckersTheme.fieldBorderColor2
                        //CheckersTheme.selectedBorderColor = CheckersTheme.selectedBorderColor2
                        CheckersTheme.blackPlayerColor = CheckersTheme.blackPlayerColor2
                        CheckersTheme.whitePlayerColor = CheckersTheme.whitePlayerColor2
                        CheckersTheme.blackPieceBorderColor = CheckersTheme.blackPieceBorderColor2
                        CheckersTheme.whitePieceBorderColor = CheckersTheme.whitePieceBorderColor2
                    }

                    if(currentIndex == 1) {
                        console.log("cosmic")
                        CheckersTheme.backgroundColor = CheckersTheme.backgroundColor3
                        CheckersTheme.buttonColor = CheckersTheme.buttonColor3
                        CheckersTheme.buttonBorderColor = CheckersTheme.buttonBorderColor3
                        CheckersTheme.fontColor = CheckersTheme.fontColor3
                        CheckersTheme.playableFieldColor = CheckersTheme.playableFieldColor3
                        CheckersTheme.notPlayableFieldColor = CheckersTheme.notPlayableFieldColor3
                        CheckersTheme.fieldBorderColor = CheckersTheme.fieldBorderColor3
                        //CheckersTheme.selectedBorderColor = CheckersTheme.selectedBorderColor3
                        CheckersTheme.blackPlayerColor = CheckersTheme.blackPlayerColor3
                        CheckersTheme.whitePlayerColor = CheckersTheme.whitePlayerColor3
                        CheckersTheme.blackPieceBorderColor = CheckersTheme.blackPieceBorderColor3
                        CheckersTheme.whitePieceBorderColor = CheckersTheme.whitePieceBorderColor3
                    }

                    if(currentIndex == 2) {
                        console.log("fantasy")
                        CheckersTheme.backgroundColor = CheckersTheme.backgroundColor4
                        CheckersTheme.buttonColor = CheckersTheme.buttonColor4
                        CheckersTheme.buttonBorderColor = CheckersTheme.buttonBorderColor4
                        CheckersTheme.fontColor = CheckersTheme.fontColor4
                        CheckersTheme.playableFieldColor = CheckersTheme.playableFieldColor4
                        CheckersTheme.notPlayableFieldColor = CheckersTheme.notPlayableFieldColor4
                        CheckersTheme.fieldBorderColor = CheckersTheme.fieldBorderColor4
                        //CheckersTheme.selectedBorderColor = CheckersTheme.selectedBorderColor4
                        CheckersTheme.blackPlayerColor = CheckersTheme.blackPlayerColor4
                        CheckersTheme.whitePlayerColor = CheckersTheme.whitePlayerColor4
                        CheckersTheme.blackPieceBorderColor = CheckersTheme.blackPieceBorderColor4
                        CheckersTheme.whitePieceBorderColor = CheckersTheme.whitePieceBorderColor4
                    }

                    if(currentIndex == 3) {
                        console.log("brony")
                        CheckersTheme.backgroundColor = CheckersTheme.backgroundColor5
                        CheckersTheme.buttonColor =  CheckersTheme.buttonColor5
                        CheckersTheme.buttonBorderColor = CheckersTheme.buttonBorderColor5
                        CheckersTheme.fontColor = CheckersTheme.fontColor5
                        CheckersTheme.playableFieldColor = CheckersTheme.playableFieldColor5
                        CheckersTheme.notPlayableFieldColor = CheckersTheme.notPlayableFieldColor5
                        CheckersTheme.fieldBorderColor = CheckersTheme.fieldBorderColor5
                        //CheckersTheme.selectedBorderColor = CheckersTheme.selectedBorderColor5
                        CheckersTheme.blackPlayerColor = CheckersTheme.blackPlayerColor5
                        CheckersTheme.whitePlayerColor = CheckersTheme.whitePlayerColor5
                        CheckersTheme.blackPieceBorderColor = CheckersTheme.blackPieceBorderColor5
                        CheckersTheme.whitePieceBorderColor = CheckersTheme.whitePieceBorderColor5
                    }
                    checkersModelInstance.resetModel()
                    //Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                    //                     pieceSeparatorX, pieceSeparatorY)
                }
            }
        */
        }
    }

    Row {
        id: optionsButtonsRow
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
