import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0
import checkers.model

Item {
    id: gameBoard

    CheckersModel {
        id: checkersModelInstance

        Component.onCompleted: {
            checkersModelInstance.resetModel()
        }
    }

    Grid {
        anchors.fill: parent
        columns: checkersModelInstance.getColumnsNo()
        rows: checkersModelInstance.getRowsNo()

        Repeater {
            model: checkersModelInstance.getColumnsNo() * checkersModelInstance.getRowsNo()

            Rectangle {
                id: rec
                width: parent.width / checkersModelInstance.getColumnsNo()
                height: parent.height / checkersModelInstance.getRowsNo()
                border.width: rec.width * 0.05
                border.color: 'black'

            }
        }
    }
}
