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

                Component.onCompleted: {
                    //console.log("Rectangle idx: ", index, "column: ", column, "row: ", row)
                    //console.log("role: ", checkersModelInstance.data(modelIndex, CheckersModel.isPlayableRole))
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

            //property double pieceSeparatorX: (fieldWidth - pieceWidth) / 2
            //property double pieceSeparatorY: (fieldHeight - pieceHeight) / 2

            width: pieceRep.pieceWidth
            height: pieceRep.pieceHeight
            //x: column * fieldWidth + (fieldWidth * ( CheckersTheme.pieceDimensionModificator / 5) )
            //y: row * fieldHeight + (fieldHeight * ( CheckersTheme.pieceDimensionModificator / 5) )
            x: (column * fieldWidth) + pieceSeparatorX //(fieldWidth * ( CheckersTheme.pieceDimensionModificator / 5) )
            y: (row * fieldHeight) + pieceSeparatorY //+ (fieldHeight * ( CheckersTheme.pieceDimensionModificator / 5) )

            visible: checkersModelInstance.isPiecePresent(modelIndex)
            color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePlayerColor : CheckersTheme.blackPlayerColor
            border.color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePieceBorderColor : CheckersTheme.blackPieceBorderColor

            Component.onCompleted: {
                //console.log("**************************************************************************************")
                //console.log("INDEX: ", index, "piece: ", piece)
                //console.log("piece on completed: ", pieceStatus)
                //console.log("x: ", piece.x, "y: ", piece.y)                                                           // coordinates somehow not initialized and not visible at the moment
                //console.log("playable: ", checkersModelInstance.data(modelIndex, CheckersModel.IsPlayableRole))
                //console.log("coordinates: ", checkersModelInstance.data(modelIndex, CheckersModel.FieldNameRole))
                //console.log("**************************************************************************************")
            }

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
                    //console.log("PRESSED:")
                    //console.log("   model index:", modelIndex)
                    //console.log("   pieceRep index: ", index)
                }
                onReleased: {
                    var newCooLeftUpX = pieceRep.itemAt(index).x
                    var newCooLeftUpY = pieceRep.itemAt(index).y
                    var newCooRightUpX = pieceRep.itemAt(index).x + pieceWidth
                    var newCooRightUpY = pieceRep.itemAt(index).y
                    var newCooLeftBottomX = pieceRep.itemAt(index).x
                    var newCooLeftBottomY = pieceRep.itemAt(index).y + pieceHeight
                    var newCooRightBottomX = pieceRep.itemAt(index).x + pieceWidth
                    var newCooRightBottomY = pieceRep.itemAt(index).y

                    var newAverageX = ( newCooLeftUpX + newCooRightUpX + newCooLeftBottomX + newCooRightBottomX ) / 4
                    var newAverageY = ( newCooLeftUpY + newCooRightUpY + newCooLeftBottomY + newCooRightBottomY ) / 4
/*
                    console.log("RELEASED:")
                    console.log("   pieceWidth:", pieceWidth)
                    console.log("   pieceHeight: ", pieceHeight)
                    console.log("   newCooLeftUpX: ", newCooLeftUpX)
                    console.log("   newCooLeftUpY: ", newCooLeftUpY)
                    console.log("   newCooRightUpX: ", newCooRightUpX)
                    console.log("   newCooRightUpY: ", newCooRightUpY)
                    console.log("   newCooLeftBottomX: ", newCooLeftBottomX)
                    console.log("   newCooLeftBottomY: ", newCooLeftBottomY)
                    console.log("   newCooRightBottomX: ", newCooRightBottomX)
                    console.log("   newCooRightBottomY: ", newCooRightBottomY)
                    console.log("   newAverageX: ", newAverageX)
                    console.log("   newAverageY: ", newAverageY)
*/
                    //***
                    if( (checkersModelInstance.getPieceColor(modelIndex) === true && game.player === CheckersModel.Player.white ) ||
                        (checkersModelInstance.getPieceColor(modelIndex) === false && game.player === CheckersModel.Player.black ) ) {

                        //***
                        if(checkersModelInstance.isMoveValid(modelIndex, newAverageX, newAverageY)) {
                            console.log("move valid")
                            var modelIndexToMove = checkersModelInstance.getModelIndexFromGivenCoordinates(newAverageX, newAverageY)
                            console.log("model index: ", modelIndex)
                            console.log("model index to move: ", modelIndexToMove)

                            //SWAP FIELDS VALUES:

                            var emptyPieceData = checkersModelInstance.data(modelIndexToMove, CheckersModel.PieceRole)
                            console.log("field to move before swap: ", emptyPieceData)
                            console.log("field to move data color: ", emptyPieceData.player)
                            console.log("field to move data type: ", emptyPieceData.type)

                            var pieceData = checkersModelInstance.data(modelIndex, CheckersModel.PieceRole)
                            console.log("piece data: ", pieceData)
                            console.log("piece data color: ", pieceData.player)
                            console.log("piece data type: ", pieceData.type)

                            checkersModelInstance.setData(modelIndexToMove, pieceData, CheckersModel.PieceRole)
                            checkersModelInstance.setData(modelIndex, emptyPieceData, CheckersModel.PieceRole)

                            console.log("field to move after swap: ", checkersModelInstance.data(modelIndexToMove, CheckersModel.PieceRole))
                            //console.log("field to move after swap data color: ", emptyPieceData.player)
                            //console.log("field to move after swap data type: ", emptyPieceData.type)

                            console.log("piece data after swap: ", checkersModelInstance.data(modelIndex, CheckersModel.PieceRole))
                            //console.log("piece data color after swap: ", pieceData.player)
                            //console.log("piece data type after swap: ", pieceData.type)

                            var fieldWidth = fieldRep.itemAt(1).x - fieldRep.itemAt(0).x
                            var fieldHeight = fieldRep.itemAt(checkersModelInstance.getColumnsNo()).y - fieldRep.itemAt(0).y

                            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                                 pieceSeparatorX, pieceSeparatorY)

                            Js.centerAllPiecesOnFields(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep)

                            if(game.player === CheckersModel.Player.white) {
                                game.player = CheckersModel.Player.black
                            }
                            else {
                                game.player = CheckersModel.Player.white
                            }
                        }
                        else {
                            console.log("move not valid")
                            Js.centerAllPiecesOnFields(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep)
                        }
                    }
                    else {
                        console.log("NOT YOUR COLOR !")
                        Js.centerAllPiecesOnFields(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep)
                    }
                }
            }
        }
    }

    onReset:  {
        checkersModelInstance.resetModel()
        Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                             pieceSeparatorX, pieceSeparatorY)
    }

    onWidthChanged: {
        if(completed) {

            //console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
            //console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                 pieceSeparatorX, pieceSeparatorY)
        }
    }

    onHeightChanged: {
        if(completed) {

            //console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
            //console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                 pieceSeparatorX, pieceSeparatorY)
        }
    }

    Component.onCompleted: {
        if(!completed) {

            //console.log("ON COMPLETED: ")
            //console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
            //console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

            Js.updateCoordinates(checkersModelInstance, CheckersModel, CheckersTheme, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                                 pieceSeparatorX, pieceSeparatorY)

            completed = true
        }
    }
}

