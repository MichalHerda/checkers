import QtQuick
import QtQuick.Controls
import Checkers 1.0
import checkers.model

import "frontEnd.js" as Js

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Checkers")
    color: CheckersTheme.backgroundColor

    property bool rotateGameBoard: false
    property bool completed: false

    property double buttonWidth: root.width * 0.28
    property double buttonHeight: root.height * 0.075
    property double buttonsSeparatorX: root.width * 0.04

    GameBoard {
        id: checkersGameBoard
        property double fieldWidth:  checkersGameBoard.width / checkersModelInstance.getColumnsNo()
        property double fieldHeight:  checkersGameBoard.height / checkersModelInstance.getRowsNo()
        property double pieceWidth: fieldWidth * CheckersTheme.pieceDimensionModificator
        property double pieceHeight: fieldHeight * CheckersTheme.pieceDimensionModificator
        property double pieceSeparatorX: (fieldWidth - pieceWidth) / 2
        property double pieceSeparatorY: (fieldHeight - pieceHeight) / 2

        //property var fieldRep: checkersGameBoard.fieldRep
        //property var pieceRep: checkersGameBoard.pieceRep

        anchors.centerIn: parent
        width: root.width * 0.5
        height: root.height * 0.675
        transformOrigin: Item.Center
        rotation: rotateGameBoard ? 180 : 0
    }

    Button {
        id: testButton
        width: buttonWidth
        height: buttonHeight
        text: "TEST BUTTON"
        x: buttonsSeparatorX
        y: parent.height - ( parent.height * 0.125 )

        background: Rectangle {
            anchors.fill: parent
            color: CheckersTheme.buttonColor
        }

        onClicked: {
            checkersModelInstance.printModel()
        }
    }

    Button {
        id: rotateButton
        width: buttonWidth
        height: buttonHeight
        text: "ROTATE"
        x: ( buttonsSeparatorX * 2 ) + buttonWidth
        y: parent.height - ( parent.height * 0.125 )

        background: Rectangle {
            anchors.fill: parent
            color: CheckersTheme.buttonColor
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
        text: "RESTART"
        x: ( buttonsSeparatorX * 3 ) + ( buttonWidth * 2 )
        y: parent.height - ( parent.height * 0.125 )

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
            color: CheckersTheme.buttonColor
        }

        onClicked: {
            checkersGameBoard.emitReset()
        }
    }
}
