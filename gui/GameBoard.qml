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
            for(var i = 0; i < rangeArray.length; i++) {
                console.log("range for index ", modelIndex, ": ", rangeArray)
                console.log("rangeArray idx: ", i)
            }
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
                        console.log("CoordinatesRole: ", checkersModelInstance.data(modelIndex, CheckersModel.CoordinatesRole))
                        console.log("IsPlayableRole: ", checkersModelInstance.data(modelIndex, CheckersModel.IsPlayableRole))
                        console.log("PieceRole: ", checkersModelInstance.data(modelIndex, CheckersModel.PieceRole))
                        console.log("RangeRole: ", checkersModelInstance.data(modelIndex, CheckersModel.RangeRole))
                        //console.log("CaptureAvailableRole: ", checkersModelInstance.data(modelIndex, CheckersModel.CaptureAvailableRole))
                        //console.log("MultiCaptureRole: ", checkersModelInstance.data(modelIndex, CheckersModel.MultiCaptureRole))
                        console.log("IsSelectedRole: ", checkersModelInstance.data(modelIndex, CheckersModel.IsSelectedRole))
                    */
                        getCoo(rec)
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
                property double fieldHeight:  parent.height / checkersModelInstance.getColumnsNo()

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
                    console.log("coordinates: ", checkersModelInstance.data(modelIndex, CheckersModel.CoordinatesRole))
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
                        console.log("INDEX: ", index, "COO: ", checkersModelInstance.data(modelIndex, CheckersModel.CoordinatesRole))
                        console.log("piece clicked. its range: ", piece.pieceRange)
                        getCoo(piece)

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
