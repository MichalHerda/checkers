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

    function getCoo(piece) {
        console.log("show ", piece, "x: ", piece.x, "y: ", piece.y)
        let coordinates = { x: piece.x, y: piece.y };
        return coordinates;
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

    function getCoordinates(repeater, width, height) {

        var coordinates = []

        var itemsNo = repeater.count

        for(let i = 0; i < itemsNo; i++) {
            //console.log("   repeater.itemAt(", i, ").x: ", repeater.itemAt(i).x)
            //console.log("   repeater.itemAt(", i, ").y: ", repeater.itemAt(i).y)
            coordinates.push(repeater.itemAt(i).x);                // topLeftX
            coordinates.push(repeater.itemAt(i).y);                // topLeftY
            coordinates.push(repeater.itemAt(i).x + fieldWidth);   // topRightX
            coordinates.push(repeater.itemAt(i).y);                // topRightY
            coordinates.push(repeater.itemAt(i).x);                // bottomLeftX
            coordinates.push(repeater.itemAt(i).y + fieldHeight);  // bottomLeftY
            coordinates.push(repeater.itemAt(i).x + fieldWidth);   // bottomRightX
            coordinates.push(repeater.itemAt(i).y + fieldHeight);  // bottomRightY
        }

        console.log("SET COORDINATES FUNCTION: ")
        console.log("   coordinates array size: ", coordinates.length)

        return coordinates
    }

    function centerAllPiecesOnFields(repeater, pieceRepeater) {

        console.log("centerAllPiecesOnFields function")
        console.log("   pieceRepeater size: ", pieceRepeater.count)
        var itemsNo = repeater.count
        var modelNo = checkersModelInstance.getRowsNo() * checkersModelInstance.getColumnsNo()

        if(itemsNo === modelNo) {
            console.log("   modelNo equals itemNo !")
            var repeaterIndex = 0

            for(let row = 0; row < checkersModelInstance.getRowsNo(); row++) {
                for(let col = 0; col < checkersModelInstance.getColumnsNo(); col++) {
                    console.log("   repeater index: ", repeaterIndex)

                    var modelIndex = checkersModelInstance.getIndex(row, col)
                    if(checkersModelInstance.isPiecePresent(modelIndex)) {

                        console.log("   center piece, row: ", row, "column: ", col )

                        var coordinates = checkersModelInstance.data(modelIndex, CheckersModel.PieceCoordinatesRole);
                        console.log("   coordinates: ", coordinates)
                        var topLeft = coordinates.topLeft
                        var topRight = coordinates.topRight
                        var bottomLeft = coordinates.bottomLeft
                        var bottomRight = coordinates.bottomRight
                        console.log("   topLeft: ", topLeft)
                        console.log("   topRight: ", topRight )
                        console.log("   bottomLeft: ", bottomLeft)
                        console.log("   bottomRight: ", bottomRight )

                        pieceRepeater.itemAt(repeaterIndex).x = topLeft.x
                        pieceRepeater.itemAt(repeaterIndex).y = topLeft.y
                    }
                    else {
                        console.log("piece not present, no item to center")
                    }
                    repeaterIndex++
                }
            }
        }
        else {
            console.log("   modelNo does not equal itemNo !")
        }
    }

    function displayCoordinates(coordinates) {
        for (let i = 0; i < coordinates.length; i += 8) {
            console.log("Item no. ", i / 8, ": ");
            console.log("  topLeft: x:", coordinates[i], "y:", coordinates[i + 1]);
            console.log("  topRight: x:", coordinates[i + 2], "y:", coordinates[i + 3]);
            console.log("  bottomLeft: x:", coordinates[i + 4], "y:", coordinates[i + 5]);
            console.log("  bottomRight: x:", coordinates[i + 6], "y:", coordinates[i + 7]);
        }
    }

    function updateCoordinates(fieldRep, pieceRep) {
        var fieldsCoordinates = getCoordinates(fieldRep, fieldWidth, fieldHeight)
        var piecesCoordinates = getCoordinates(pieceRep, pieceWidth, pieceHeight)
        checkersModelInstance.updateFieldsCoordinates(fieldsCoordinates)
        checkersModelInstance.updatePiecesCoordinates(piecesCoordinates)
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

        onWidthChanged: {
            if(completed) {
                /*
                var fieldWidth = fieldRep.itemAt(1).x - fieldRep.itemAt(0).x
                var fieldHeight = fieldRep.itemAt(checkersModelInstance.getColumnsNo()).y - fieldRep.itemAt(0).y

                console.log("WIDTH CHANGED: ")
                console.log("   rows no: ", checkersModelInstance.getRowsNo())
                console.log("   columns no: ", checkersModelInstance.getColumnsNo())
                console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
                console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

                for(let i = 0; i < fieldRep.count; i++) {
                    console.log("   repeater.itemAt(", i, ").x: ", fieldRep.itemAt(i).x)
                    console.log("   repeater.itemAt(", i, ").y: ", fieldRep.itemAt(i).y)
                }
                */
                console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
                console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

                updateCoordinates(fieldRep, pieceRep)
            }
        }

        onHeightChanged: {
            if(completed) {
                /*
                var fieldWidth = fieldRep.itemAt(1).x - fieldRep.itemAt(0).x
                var fieldHeight = fieldRep.itemAt(checkersModelInstance.getColumnsNo()).y - fieldRep.itemAt(0).y

                console.log("HEIGHT CHANGED: ")
                console.log("   rows no: ", checkersModelInstance.getRowsNo())
                console.log("   columns no: ", checkersModelInstance.getColumnsNo())
                console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
                console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

                for(let i = 0; i < fieldRep.count; i++) {
                    console.log("   repeater.itemAt(", i, ").x: ", fieldRep.itemAt(i).x)
                    console.log("   repeater.itemAt(", i, ").y: ", fieldRep.itemAt(i).y)
                }
                */
                console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
                console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

                updateCoordinates(fieldRep, pieceRep)
            }
        }

        Component.onCompleted: {
            if(!completed) {
                /*
                var fieldWidth = fieldRep.itemAt(1).x - fieldRep.itemAt(0).x
                var fieldHeight = fieldRep.itemAt(checkersModelInstance.getColumnsNo()).y - fieldRep.itemAt(0).y

                console.log("COMPONENT.ON.COMPLETED: ")
                console.log("   rows no: ", checkersModelInstance.getRowsNo())
                console.log("   columns no: ", checkersModelInstance.getColumnsNo())
                console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
                console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

                for(let i = 0; i < fieldRep.count; i++) {
                    console.log("   repeater.itemAt(", i, ").x: ", fieldRep.itemAt(i).x)
                    console.log("   repeater.itemAt(", i, ").y: ", fieldRep.itemAt(i).y)
                }
                */
                console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)
                console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

                updateCoordinates(fieldRep, pieceRep)

                completed = true
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
            property var modelIndex: getFieldIndex(row, column)

            property var pieceStatus: checkersModelInstance.data(modelIndex, CheckersModel.PieceRole)
            property var pieceRange: checkersModelInstance.data(modelIndex, CheckersModel.RangeRole)

            width: pieceRep.pieceWidth
            height: pieceRep.pieceHeight
            x: column * fieldWidth + (fieldWidth * ( CheckersTheme.pieceDimensionModificator / 5) )
            y: row * fieldHeight + (fieldHeight * ( CheckersTheme.pieceDimensionModificator / 5) )

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
                    console.log("PRESSED:")
                    console.log("   model index:", modelIndex)
                    console.log("   pieceRep index: ", index)
                }
                onReleased: {
                    var newCooLeftUpX = pieceRep.itemAt(index).x
                    var newCooLeftUpY = pieceRep.itemAt(index).y
                    var newCooRightUpX = pieceRep.itemAt(index).x + piece.width
                    var newCooRightUpY = pieceRep.itemAt(index).y
                    var newCooLeftBottomX = pieceRep.itemAt(index).x
                    var newCooLeftBottomY = pieceRep.itemAt(index).y + piece.height
                    var newCooRightBottomX = pieceRep.itemAt(index).x + piece.width
                    var newCooRightBottomY = pieceRep.itemAt(index).y

                    var newAverageX = ( newCooLeftUpX + newCooRightUpX + newCooLeftBottomX + newCooRightBottomX ) / 4
                    var newAverageY = ( newCooLeftUpY + newCooRightUpY + newCooLeftBottomY + newCooRightBottomY ) / 4
/*
                    console.log("RELEASED:")
                    console.log("   pieceWidth:", piece.width)
                    console.log("   pieceHeight: ", piece.height)
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

                        updateCoordinates(fieldRep, pieceRep)

                        centerAllPiecesOnFields(fieldRep, pieceRep)

                    }
                    else {
                        console.log("move not valid")
                        centerAllPiecesOnFields(fieldRep, pieceRep)
                    }

                    /*
                    TODO:
                        1. Oblicz koordynaty: wierzchołków pionka i środka pionka
                        2. Znajdź indeks pola wewnątrz którego znajduje się środek pionka
                        3. Sprawdź, czy znalezione pole znajduje się w zasięgu pionka (RangeRole)
                        4. Jeśli nie: wróć pionkiem do poprzedniej pozycji
                        5. Jeśli tak: wycentruj pionek tak, żeby jego środek był równy FieldCenterRole
                    */

                }
            }
        }
    }
}

