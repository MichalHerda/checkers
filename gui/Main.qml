import QtQuick
import QtQuick.Controls
import Checkers 1.0
import checkers.model


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Checkers")
    color: CheckersTheme.backgroundColor

    //CheckersModel {
    //    id: checkersModelInstance
    //
    //    Component.onCompleted: {
    //        checkersModelInstance.resetModel()
    //    }
    //}

    GameBoard {
        id: checkersGameBoard
        anchors.centerIn: parent
        width: parent.width * 0.5
        height: parent.height * 0.5
    }

    Button {
        id: testButton
        width: parent.width * 0.35
        height: parent.height * 0.1
        text: "TEST BUTTON"
        x: parent.width * 0.05
        y: parent.height - ( parent.height * 0.15 )

        background: Rectangle {
            anchors.fill: parent
            color: CheckersTheme.buttonColor
        }

        onClicked: {
            checkersGameBoard.checkersModelInstance.printModel()
        }
    }
}
