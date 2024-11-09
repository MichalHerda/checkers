import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0
import checkers.model

//potrzebna jest funkcja, która na podstawie zaznaczonego pionka i na podstawie rangeRole, określi koordynaty dla pól które są w zasięgu
//jedną z opcji jest utworzenie kolejnej roli: indexRole - ale to jest raczej dyskusyjne
//obecnym problemem jest to, że funkcje które stworzyłem do pobrania koordynatów, pobierają je na podstawie zaznaczonego pola lub zaznaczonego pionka
//należy rozwiązać problem, jak podać sąsiednie pola planszy do gry celem uzyskania koordynatów

Item {
    id: root
    property var fieldCoordinates: []

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

    function setFieldCoordinates(repeater) {

        fieldCoordinates.length = 0

        var fieldWidth = repeater.itemAt(1).x - repeater.itemAt(0).x
        var fieldHeight = repeater.itemAt(checkersModelInstance.getColumnsNo()).y - repeater.itemAt(0).y

        console.log("fieldWidth: ", fieldWidth, "fieldHeight: ", fieldHeight)

        var itemsNo = repeater.count

        for(let i = 0; i < itemsNo; i++) {
            fieldCoordinates.push(repeater.itemAt(i).x);                // topLeftX
            fieldCoordinates.push(repeater.itemAt(i).y);                // topLeftY
            fieldCoordinates.push(repeater.itemAt(i).x + fieldWidth);   // topRightX
            fieldCoordinates.push(repeater.itemAt(i).y);                // topRightY
            fieldCoordinates.push(repeater.itemAt(i).x);                // bottomLeftX
            fieldCoordinates.push(repeater.itemAt(i).y + fieldHeight);  // bottomLeftY
            fieldCoordinates.push(repeater.itemAt(i).x + fieldWidth);   // bottomRightX
            fieldCoordinates.push(repeater.itemAt(i).y + fieldHeight);  // bottomRightY
        }

        console.log("fieldCoordinates array size: ", fieldCoordinates.length)
        displayCoordinates()
        checkersModelInstance.updateCoordinates(fieldCoordinates)
    }

    function displayCoordinates() {
        for (let i = 0; i < fieldCoordinates.length; i += 8) {
                console.log("Item no. ", i / 8, ": ");
                console.log("  topLeft: x:", fieldCoordinates[i], "y:", fieldCoordinates[i + 1]);
                console.log("  topRight: x:", fieldCoordinates[i + 2], "y:", fieldCoordinates[i + 3]);
                console.log("  bottomLeft: x:", fieldCoordinates[i + 4], "y:", fieldCoordinates[i + 5]);
                console.log("  bottomRight: x:", fieldCoordinates[i + 6], "y:", fieldCoordinates[i + 7]);
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

                //property int row: checkersModelInstance.getRowsNo() - 1 - Math.floor(index / checkersModelInstance.getColumnsNo())
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
                        setFieldCoordinates(rep)
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
            setFieldCoordinates(rep)
            //checkersModelInstance.updateCoordinates()
        }

        onHeightChanged: {
            console.log("height changed")
            setFieldCoordinates(rep)
            //checkersModelInstance.updateCoordinates()
        }
    }

    Repeater {
        id: pieceRep
        model: checkersModelInstance.getColumnsNo() * checkersModelInstance.getRowsNo()

            Piece {
                id: piece

                //property int row: checkersModelInstance.getRowsNo() - 1 - Math.floor(index / checkersModelInstance.getColumnsNo())

                property int row: Math.floor(index / checkersModelInstance.getColumnsNo())
                property int column: index % checkersModelInstance.getColumnsNo()
                property var modelIndex: getFieldIndex(row, column)

                property double fieldWidth:  parent.width / checkersModelInstance.getColumnsNo()
                property double fieldHeight:  parent.height / checkersModelInstance.getRowsNo()

                property double pieceWidth: fieldWidth * CheckersTheme.pieceDimensionModificator
                property double pieceHeight: fieldHeight * CheckersTheme.pieceDimensionModificator

                property var pieceStatus: checkersModelInstance.data(modelIndex, CheckersModel.PieceRole)
                property var pieceRange: checkersModelInstance.data(modelIndex, CheckersModel.RangeRole)

                width: pieceWidth
                height: pieceHeight
                x: column * fieldWidth + (fieldWidth * ( CheckersTheme.pieceDimensionModificator / 5) )
                y: row * fieldHeight + (fieldHeight * ( CheckersTheme.pieceDimensionModificator / 5) )

                visible: checkersModelInstance.isPiecePresent(modelIndex)
                color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePlayerColor : CheckersTheme.blackPlayerColor
                border.color: checkersModelInstance.getPieceColor(modelIndex) ? CheckersTheme.whitePieceBorderColor : CheckersTheme.blackPieceBorderColor

                Component.onCompleted: {
                    console.log("**************************************************************************************")
                    console.log("INDEX: ", index, "piece: ", piece)
                    console.log("piece on completed: ", pieceStatus)
                    //console.log("x: ", piece.x, "y: ", piece.y)                   // coordinates somehow not initialized and not visible at the moment
                    console.log("playable: ", checkersModelInstance.data(modelIndex, CheckersModel.IsPlayableRole))
                    console.log("coordinates: ", checkersModelInstance.data(modelIndex, CheckersModel.FieldNameRole))
                    console.log("**************************************************************************************")
                }

                //Drag.active: pieceMouseArea.drag.active

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
    }
}

