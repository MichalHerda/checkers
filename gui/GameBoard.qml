import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0
import checkers.model

Item {
    id: root

    function getFieldIndex(row, column) {
        //console.log("getFieldFoo, row: ", row, "column: ", column)
        //console.log("getIdx: ", checkersModelInstance.getIndex(row, column))
        return checkersModelInstance.getIndex(row, column)
    }

    Grid {
        id: gameBoard
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
                border.width: !checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole) ? rec.width * 0.025 : rec.width * 0.08
                border.color: !checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole) ? CheckersTheme.fieldBorderColor : CheckersTheme.selectedBorderColor

                //property int row: Math.floor(index / checkersModelInstance.getColumnsNo())

                property int row: checkersModelInstance.getRowsNo() - 1 - Math.floor(index / checkersModelInstance.getColumnsNo())
                property int column: index % checkersModelInstance.getColumnsNo()
                property var modelIndex: getFieldIndex(row, column)
                property var item: checkersModelInstance.getItem(modelIndex)

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
                        checkersModelInstance.deselectAllFields()
                        console.log("1.model index: ", modelIndex)
                        checkersModelInstance.setData(modelIndex, !checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole), CheckersModel.IsSelectedRole)
                        console.log("2.model index: ", modelIndex)
                        //checkersModelInstance.itemChanged(item)
                        //console.log("3.model index: ", modelIndex)              // TODO: why modelIndex dissappears here ??????????????????????????????????????????????????

                        console.log("model index: ", modelIndex)
                        console.log("index: ", index)
                        console.log("CoordinatesRole: ", checkersModelInstance.data(modelIndex, CheckersModel.CoordinatesRole))
                        console.log("IsPlayableRole: ", checkersModelInstance.data(modelIndex, CheckersModel.IsPlayableRole))
                        console.log("PieceRole: ", checkersModelInstance.data(modelIndex, CheckersModel.PieceRole))
                        console.log("RangeRole: ", checkersModelInstance.data(modelIndex, CheckersModel.RangeRole))
                        //console.log("CaptureAvailableRole: ", checkersModelInstance.data(modelIndex, CheckersModel.CaptureAvailableRole))
                        //console.log("MultiCaptureRole: ", checkersModelInstance.data(modelIndex, CheckersModel.MultiCaptureRole))
                        console.log("IsSelectedRole: ", checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole))
                    }
                }


/*
                Piece {
                    id: piece
                    property var pieceStatus: checkersModelInstance.data(modelIndex, CheckersModel.PieceRole)
                    property var pieceRange: checkersModelInstance.data(modelIndex, CheckersModel.RangeRole)
                    visible: checkersModelInstance.isPiecePresent(modelIndex)
                    color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePlayerColor : CheckersTheme.blackPlayerColor
                    border.color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePieceBorderColor : CheckersTheme.blackPieceBorderColor
                    x: parent.width * 0.15
                    y: parent.width * 0.15
                    Component.onCompleted: {
                        //console.log("piece on completed: ", pieceStatus)
                    }

                    Drag.active: pieceMouseArea.drag.active

                    MouseArea {
                        id: pieceMouseArea
                        anchors.fill: parent
                        drag.target: piece
                        drag.axis: Drag.XAndYAxis
                        //drag.minimumX: 0
                        drag.maximumX: gameBoard.width - piece.width
                        drag.maximumY: gameBoard.height - piece.height
                        onClicked: {
                            console.log("piece clicked. its range: ", piece.pieceRange)

                        }
                        onPressed: {
                            console.log("pressed")

                        }
                        onReleased: {
                            console.log("released")
                        }
                    }
                }
*/

                Component.onCompleted: {
                    //console.log("Rectangle idx: ", index, "column: ", column, "row: ", row)
                    //console.log("role: ", checkersModelInstance.data(modelIndex, CheckersModel.isPlayableRole))
                }
            }
        }

        Repeater {
            id: pieceRep
            model: checkersModelInstance.getColumnsNo() * checkersModelInstance.getRowsNo()

                Piece {
                    id: piece
                    width: parent.width / checkersModelInstance.getColumnsNo()
                    height: parent.height / checkersModelInstance.getRowsNo()
                    x: parent.width * 0.15
                    y: parent.width * 0.15

                    property int row: checkersModelInstance.getRowsNo() - 1 - Math.floor(index / checkersModelInstance.getColumnsNo())
                    property int column: index % checkersModelInstance.getColumnsNo()
                    property var modelIndex: getFieldIndex(row, column)

                    property var pieceStatus: checkersModelInstance.data(modelIndex, CheckersModel.PieceRole)
                    property var pieceRange: checkersModelInstance.data(modelIndex, CheckersModel.RangeRole)
                    visible: checkersModelInstance.isPiecePresent(modelIndex)
                    color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePlayerColor : CheckersTheme.blackPlayerColor
                    border.color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePieceBorderColor : CheckersTheme.blackPieceBorderColor

                    Component.onCompleted: {
                        //console.log("piece on completed: ", pieceStatus)
                    }

                    Drag.active: pieceMouseArea.drag.active

                    MouseArea {
                        id: pieceMouseArea
                        anchors.fill: parent
                        drag.target: piece
                        drag.axis: Drag.XAndYAxis
                        //drag.minimumX: 0
                        drag.maximumX: gameBoard.width - piece.width
                        drag.maximumY: gameBoard.height - piece.height
                        onClicked: {
                            console.log("piece clicked. its range: ", piece.pieceRange)

                        }
                        onPressed: {
                            console.log("pressed")

                        }
                        onReleased: {
                            console.log("released")
                        }
                    }
                }
        }
        Connections {
            target: checkersModelInstance
            function onItemChanged(item) {
                console.log("ITEM CHANGED")
                let currentModel = rep.model;
                rep.model = null;
                rep.model = currentModel;
            }
        }
    }
}
