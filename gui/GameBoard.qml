import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0
import checkers.model
import "frontEnd.js" as Js

Item {
    id: root

    signal reset()

    function emitReset() {
        console.log("Emitting reset signal from GameBoard")
        reset()
    }

    function getAvailableFieldsCoo(modelIndex) {
        var rangeArray = checkersModelInstance.data(modelIndex, CheckersModel.RangeRole)

        if (!rangeArray || rangeArray.length === 0) {
           console.log("No range available for modelIndex:", modelIndex);
           return [];
        }
        else {
            for(let j = 0; j < rangeArray.length; j++) {
                console.log("range for index ", modelIndex, ": ", rangeArray)
                console.log("rangeArray idx: ", j)
            }
        }
    }

    function handleVisibilityChanged() {
        console.log("handle visibility changed function")
        if(completed) {
            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, GameController, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                 pieceSeparatorX, pieceSeparatorY)
        }
    }

    Grid {
        id: gameBoard
        anchors.fill: parent
        columns: checkersModelInstance.getColumnsNo()
        rows: checkersModelInstance.getRowsNo()

        Repeater {
            id: fieldRep
            model: checkersModelInstance.getColumnsNo() * checkersModelInstance.getRowsNo()

            Rectangle {
                id: rec
                width: parent.width / checkersModelInstance.getColumnsNo()
                height: parent.height / checkersModelInstance.getRowsNo()
                border.width: !checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole) ? rec.width * 0.025 : rec.width * 0.08
                border.color: !checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole) ? CheckersTheme.fieldBorderColor : CheckersTheme.selectedBorderColor

                property int row: Math.floor(index / checkersModelInstance.getColumnsNo())
                property int column: index % checkersModelInstance.getColumnsNo()
                property var modelIndex: Js.getFieldIndex(row, column, checkersModelInstance)
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
                        console.log("model index: ", modelIndex)
                        console.log("capture available role for idx ", modelIndex, ": ", checkersModelInstance.data(modelIndex, CheckersModel.CaptureAvailableRole))
                        //console.log("multi capture role for idx ", modelIndex, ": ", checkersModelInstance.data(modelIndex, CheckersModel.MultiCaptureRole))
                        console.log("PieceRole: ", checkersModelInstance.data(modelIndex, CheckersModel.PieceRole))
                        console.log("RangeRole: ", checkersModelInstance.data(modelIndex, CheckersModel.RangeRole))
                        console.log("is king: ", checkersModelInstance.getPieceType(modelIndex))
                        console.log("score: \n", checkersModelInstance.showScore())
                    /*
                        checkersModelInstance.deselectAllFields()
                        console.log("1.model index: ", modelIndex)
                        checkersModelInstance.setData(modelIndex, !checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole), CheckersModel.IsSelectedRole)
                        console.log("2.model index: ", modelIndex)
                        //checkersModelInstance.itemChanged(item)
                        //console.log("3.model index: ", modelIndex)              // TODO: why modelIndex dissappears here ??????????????????????????????????????????????????

                        console.log("model index: ", modelIndex)
                        console.log("index: ", index)
                        console.log("FieldNameRole: ", checkersModelInstance.data(modelIndex, CheckersModel.FieldNameRole))
                        console.log("IsPlayableRole: ", checkersModelInstance.data(modelIndex, CheckersModel.IsPlayableRole))
                        console.log("PieceRole: ", checkersModelInstance.data(modelIndex, CheckersModel.PieceRole))
                        console.log("RangeRole: ", checkersModelInstance.data(modelIndex, CheckersModel.RangeRole))
                        //console.log("CaptureAvailableRole: ", checkersModelInstance.data(modelIndex, CheckersModel.CaptureAvailableRole))
                        //console.log("MultiCaptureRole: ", checkersModelInstance.data(modelIndex, CheckersModel.MultiCaptureRole))
                        console.log("IsSelectedRole: ", checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole))
                    */
                        //setFieldsCoordinates(fieldRep)
                        //getCoo(rec)
                    }
                }
            }
        }

        Connections {
            target: checkersModelInstance
            function onItemChanged(item) {
                console.log("ITEM CHANGED")
                let currentModel = fieldRep.model;
                fieldRep.model = null;
                fieldRep.model = currentModel;
            }
        }
    }

    Repeater {
        id: pieceRep
        model: checkersModelInstance.getColumnsNo() * checkersModelInstance.getRowsNo()

        property double fieldWidth:  parent.width / checkersModelInstance.getColumnsNo()
        property double fieldHeight:  parent.height / checkersModelInstance.getRowsNo()

        property double pieceWidth: fieldWidth * CheckersTheme.pieceDimensionModificator
        property double pieceHeight: fieldHeight * CheckersTheme.pieceDimensionModificator

        Piece {
            id: piece

            property int row: Math.floor(index / checkersModelInstance.getColumnsNo())
            property int column: index % checkersModelInstance.getColumnsNo()
            property var modelIndex: Js.getFieldIndex(row, column, checkersModelInstance)

            property var pieceStatus: checkersModelInstance.data(modelIndex, CheckersModel.PieceRole)
            property var pieceRange: checkersModelInstance.data(modelIndex, CheckersModel.RangeRole)

            width:  Math.min(pieceWidth, pieceHeight)
            height: Math.min(pieceWidth, pieceHeight)
            x: (column * fieldWidth) + pieceSeparatorX
            y: (row * fieldHeight) + pieceSeparatorY
            z: 0

            visible: checkersModelInstance.isPiecePresent(modelIndex)
            color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePlayerColor : CheckersTheme.blackPlayerColor
            border.color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePieceBorderColor : CheckersTheme.blackPieceBorderColor
            kingSign.color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePieceBorderColor : CheckersTheme.blackPieceBorderColor
            isKing: checkersModelInstance.getPieceType(modelIndex)

            MouseArea {
                id: pieceMouseArea
                anchors.fill: parent
                drag.target: piece
                drag.axis: Drag.XAndYAxis
                drag.minimumX: 0
                drag.minimumY: 0
                drag.maximumX: gameBoard.width - piece.width
                drag.maximumY: gameBoard.height - piece.height
                onClicked: {
                    //console.log("INDEX: ", index, "COO: ", checkersModelInstance.data(modelIndex, CheckersModel.FieldNameRole))
                    //console.log("   piece clicked. its range: ", piece.pieceRange)
                    //console.log("   coordinates: ", checkersModelInstance.data(modelIndex, CheckersModel.PieceCoordinatesRole))
                    //getCoo(piece)
                }
                onPressed: {
                    pieceRep.itemAt(index).z = 1
                }
                onReleased: {
                    pieceRep.itemAt(index).z = 0
                    var newAverageX = Js.calculatePieceCenterX(pieceRep, pieceWidth, index)
                    var newAverageY = Js.calcultaePieceCenterY(pieceRep, pieceHeight, index)

                    if(GameController.isPlayersOwnPiece(modelIndex)) {
                        console.log("players own piece")
                        if(GameController.isMoveValid(modelIndex, newAverageX, newAverageY)) {
                            var mustCapture = GameController.mustCapture(GameController.player)
                            GameController.executeMove(modelIndex, newAverageX, newAverageY)

                            var fieldWidth = fieldRep.itemAt(1).x - fieldRep.itemAt(0).x
                            var fieldHeight = fieldRep.itemAt(checkersModelInstance.getColumnsNo()).y - fieldRep.itemAt(0).y

                            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, GameController, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                                 pieceSeparatorX, pieceSeparatorY)

                            GameController.evaluatePromotionToKing(modelIndex, newAverageX, newAverageY)
                            Js.centerAllPiecesOnFields(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, GameController)

                            GameController.changePlayer(newAverageX, newAverageY, mustCapture)
                        }
                        else {
                            console.log("move not valid")
                            Js.centerAllPiecesOnFields(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, GameController,)
                        }
                    }
                    else {
                        console.log("NOT YOUR COLOR !")
                        Js.centerAllPiecesOnFields(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, GameController,)
                    }
                }
            }
        }
    }

    onReset:  {
        GameController.resetModel()
        Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, GameController, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                             pieceSeparatorX, pieceSeparatorY)
    }

    onWidthChanged: {
        if(completed) {
            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, GameController, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                 pieceSeparatorX, pieceSeparatorY)
        }
    }

    onHeightChanged: {
        if(completed) {
            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, GameController, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                 pieceSeparatorX, pieceSeparatorY)
        }
    }

    Component.onCompleted: {
        if(!completed) {
            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, GameController, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                 pieceSeparatorX, pieceSeparatorY)
            completed = true
        }
    }
}

