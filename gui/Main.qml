import QtQuick
import QtQuick.Controls
import Checkers 1.0
import checkers.model


Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Checkers")
    color: CheckersTheme.backgroundColor

    property bool rotateGameBoard: false
    property bool completed: false

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
    }

    Button {
        id: testButton
        width: parent.width * 0.35
        height: parent.height * 0.075
        text: "TEST BUTTON"
        x: parent.width * 0.05
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
        width: parent.width * 0.35
        height: parent.height * 0.075
        text: "ROTATE"
        x: parent.width * 0.05 + ( testButton.width * 1.5 )
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
}
