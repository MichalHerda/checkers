import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0
import checkers.model

Item {
    id: gameBoard

    function getFieldIndex(row, column) {
        console.log("getFieldFoo, row: ", row, "column: ", column)
        //console.log("role: ", checkersModelInstance.data(getFieldIndex(row, column), checkersModelInstance.IsPlayableRole))
        console.log("getIdx: ", checkersModelInstance.index(row, column))
        return checkersModelInstance.index(row, column)
    }

    //CheckersModel {
    //    id: checkersModelInstance
    //
    //    Component.onCompleted: {
    //        checkersModelInstance.resetModel()
    //    }
    //}

    Grid {
        anchors.fill: parent
        columns: checkersModelInstance.getColumnsNo()
        rows: checkersModelInstance.getRowsNo()

        Repeater {
            id: rep
            model: checkersModelInstance.getColumnsNo() * checkersModelInstance.getRowsNo()

            Rectangle {
                id: rec
                width: parent.width / checkersModelInstance.getColumnsNo()
                height: parent.height / checkersModelInstance.getRowsNo()
                border.width: rec.width * 0.05
                border.color: 'black'

                // Właściwe użycie index wewnątrz komponentu
                property int row: Math.floor(index / checkersModelInstance.getColumnsNo())
                property int column: index % checkersModelInstance.getColumnsNo()

                color: checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.IsPlayableRole === true ) ? "blue" : "white"

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 8
                    text: "R: " + rec.row + ", C: " + rec.column
                    color: "black"
                }

                Button {
                    id: testButton
                    anchors.fill: parent
                    opacity: 0
                    onClicked: {
                        //checkersModelInstance.printModel()
                        console.log("row: ", row, "column: ", column)
                        console.log("role: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.IsPlayableRole))
                    }
                }


                Component.onCompleted: {
                    console.log("Rectangle idx: ", index, "column: ", column, "row: ", row)
                    console.log("role: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.IsPlayableRole))
                }

            }
        }
    }
}
