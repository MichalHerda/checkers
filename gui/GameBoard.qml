import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0
import checkers.model

Item {
    id: root
    property var fieldsCoordinates: []
    property var piecesCoordinates: []



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

    function setFieldsCoordinates(repeater) {

        fieldsCoordinates.length = 0

        var fieldWidth = repeater.itemAt(1).x - repeater.itemAt(0).x
        var fieldHeight = repeater.itemAt(checkersModelInstance.getColumnsNo()).y - repeater.itemAt(0).y

        console.log("setFieldCoordinates function: ")
        console.log("   fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)

        var itemsNo = repeater.count

        for(let i = 0; i < itemsNo; i++) {
            fieldsCoordinates.push(repeater.itemAt(i).x);                // topLeftX
            fieldsCoordinates.push(repeater.itemAt(i).y);                // topLeftY
            fieldsCoordinates.push(repeater.itemAt(i).x + fieldWidth);   // topRightX
            fieldsCoordinates.push(repeater.itemAt(i).y);                // topRightY
            fieldsCoordinates.push(repeater.itemAt(i).x);                // bottomLeftX
            fieldsCoordinates.push(repeater.itemAt(i).y + fieldHeight);  // bottomLeftY
            fieldsCoordinates.push(repeater.itemAt(i).x + fieldWidth);   // bottomRightX
            fieldsCoordinates.push(repeater.itemAt(i).y + fieldHeight);  // bottomRightY
        }

        console.log("fieldsCoordinates array size: ", fieldsCoordinates.length)
        //displayCoordinates()
        checkersModelInstance.updateCoordinates(fieldsCoordinates)
    }

    function setPiecesCoordinates(repeater, pieceWidth, pieceHeight) {

        piecesCoordinates.length = 0

        console.log("setPiecesCoordinates function: ")
        console.log("   pieceWidth: ", pieceWidth, "pieceHeight: ", pieceHeight)

        var itemsNo = repeater.count

        for(let i = 0; i < itemsNo; i++) {
            piecesCoordinates.push(repeater.itemAt(i).x);                // topLeftX
            piecesCoordinates.push(repeater.itemAt(i).y);                // topLeftY
            piecesCoordinates.push(repeater.itemAt(i).x + pieceWidth);   // topRightX
            piecesCoordinates.push(repeater.itemAt(i).y);                // topRightY
            piecesCoordinates.push(repeater.itemAt(i).x);                // bottomLeftX
            piecesCoordinates.push(repeater.itemAt(i).y + pieceHeight);  // bottomLeftY
            piecesCoordinates.push(repeater.itemAt(i).x + pieceWidth);   // bottomRightX
            piecesCoordinates.push(repeater.itemAt(i).y + pieceHeight);  // bottomRightY
        }

        console.log("piecesCoordinates array size: ", piecesCoordinates.length)
        checkersModelInstance.updatePiecesCoordinates(piecesCoordinates)
    }

    function displayCoordinates() {
        for (let i = 0; i < fieldsCoordinates.length; i += 8) {
                console.log("Item no. ", i / 8, ": ");
                console.log("  topLeft: x:", fieldsCoordinates[i], "y:", fieldsCoordinates[i + 1]);
                console.log("  topRight: x:", fieldsCoordinates[i + 2], "y:", fieldsCoordinates[i + 3]);
                console.log("  bottomLeft: x:", fieldsCoordinates[i + 4], "y:", fieldsCoordinates[i + 5]);
                console.log("  bottomRight: x:", fieldsCoordinates[i + 6], "y:", fieldsCoordinates[i + 7]);
            }
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
                        setFieldsCoordinates(rep)
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
                let currentModel = rep.model;
                rep.model = null;
                rep.model = currentModel;
            }
        }

        onWidthChanged: {
            console.log("width changed")
            setFieldsCoordinates(rep)
            setPiecesCoordinates(pieceRep, pieceRep.pieceWidth, pieceRep.pieceHeight)
            //checkersModelInstance.updateCoordinates()
        }

        onHeightChanged: {
            console.log("height changed")
            setFieldsCoordinates(rep)
            setPiecesCoordinates(pieceRep, pieceRep.pieceWidth, pieceRep.pieceHeight)
            //checkersModelInstance.updateCoordinates()
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
                //drag.minimumX: 0
                drag.maximumX: gameBoard.width - piece.width
                drag.maximumY: gameBoard.height - piece.height
                onClicked: {
                    console.log("INDEX: ", index, "COO: ", checkersModelInstance.data(modelIndex, CheckersModel.FieldNameRole))
                    console.log("piece clicked. its range: ", piece.pieceRange)
                    //getCoo(piece)
                    displayCoordinates()

                }
                onPressed: {
                    console.log("pressed")
                    getCoo(piece)
                    getAvailableFieldsCoo(modelIndex)

                }
                onReleased: {
                    console.log("released")
                    getCoo(piece)
                }
            }
        }
/*
        onWidthChanged: {
            console.log("width changed")
            setPiecesCoordinates(pieceRep, pieceRep.pieceWidth, pieceRep.pieceHeight)
        }

        onHeightChanged: {
            console.log("height changed")
            setPiecesCoordinates(pieceRep, pieceRep.pieceWidth, pieceRep.pieceHeight)
        }
*/
    }
}

