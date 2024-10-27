import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0
import checkers.model

Item {
    id: gameBoard

    function getFieldIndex(row, column) {
        //console.log("getFieldFoo, row: ", row, "column: ", column)
        //console.log("getIdx: ", checkersModelInstance.getIndex(row, column))
        return checkersModelInstance.getIndex(row, column)
    }

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
                border.width: rec.width * 0.025
                border.color: CheckersTheme.fieldBorderColor

                property int row: Math.floor(index / checkersModelInstance.getColumnsNo())
                property int column: index % checkersModelInstance.getColumnsNo()
                property var modelIndex: getFieldIndex(row, column)

                color: checkersModelInstance.data(modelIndex, CheckersModel.IsPlayableRole) === true  ?
                       CheckersTheme.playableFieldColor :
                       CheckersTheme.notPlayableFieldColor

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
                        //console.log("model index: ", modelIndex)
                        console.log("CoordinatesRole: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.CoordinatesRole))
                        //console.log("IsPlayableRole: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.IsPlayableRole))
                        //console.log("PieceRole: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.PieceRole))
                        //console.log("RangeRole: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.RangeRole))
                        //console.log("CaptureAvailableRole: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.CaptureAvailableRole))
                        //console.log("MultiCaptureRole: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.MultiCaptureRole))
                        //console.log("IsSelectedRole: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.IsSelectedRole))
                    }
                }

                Piece {
                    property var pieceStatus: checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.PieceRole) ;
                    visible: checkersModelInstance.isPiecePresent(getFieldIndex(row, column))
                    color: checkersModelInstance.getPieceColor(getFieldIndex(row, column)) ? CheckersTheme.whitePlayerColor : CheckersTheme.blackPlayerColor

                    Component.onCompleted: {
                        //console.log("piece on completed: ", pieceStatus)
                    }
                }


                Component.onCompleted: {
                    //console.log("Rectangle idx: ", index, "column: ", column, "row: ", row)
                    //console.log("role: ", checkersModelInstance.data(getFieldIndex(row, column), CheckersModel.isPlayableRole))
                }
            }
        }
    }
}
