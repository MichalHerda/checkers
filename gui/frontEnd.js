.pragma library

function getFieldIndex(row, column, checkersModelInstance) {
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
        coordinates.push(repeater.itemAt(i).x + width);   // topRightX
        coordinates.push(repeater.itemAt(i).y);                // topRightY
        coordinates.push(repeater.itemAt(i).x);                // bottomLeftX
        coordinates.push(repeater.itemAt(i).y + height);  // bottomLeftY
        coordinates.push(repeater.itemAt(i).x + width);   // bottomRightX
        coordinates.push(repeater.itemAt(i).y + height);  // bottomRightY
    }

    console.log("SET COORDINATES FUNCTION: ")
    console.log("   coordinates array size: ", coordinates.length)

    return coordinates
}

function getPiecesCoordinates(repeater, width, height, pieceSeparatorX, pieceSeparatorY) {

    var coordinates = []

    var itemsNo = repeater.count

    for(let i = 0; i < itemsNo; i++) {
        //console.log("   repeater.itemAt(", i, ").x: ", repeater.itemAt(i).x)
        //console.log("   repeater.itemAt(", i, ").y: ", repeater.itemAt(i).y)
        coordinates.push(repeater.itemAt(i).x + pieceSeparatorX);                // topLeftX
        coordinates.push(repeater.itemAt(i).y + pieceSeparatorY);                // topLeftY
        coordinates.push(repeater.itemAt(i).x + pieceSeparatorX + width);        // topRightX
        coordinates.push(repeater.itemAt(i).y + pieceSeparatorY);                // topRightY
        coordinates.push(repeater.itemAt(i).x + pieceSeparatorX);                // bottomLeftX
        coordinates.push(repeater.itemAt(i).y + pieceSeparatorY + height);       // bottomLeftY
        coordinates.push(repeater.itemAt(i).x + pieceSeparatorX + width);        // bottomRightX
        coordinates.push(repeater.itemAt(i).y + pieceSeparatorY + height);       // bottomRightY
    }

    console.log("SET COORDINATES FUNCTION: ")
    console.log("   coordinates array size: ", coordinates.length)

    return coordinates
}


function centerAllPiecesOnFields(checkersModelInstance, CheckersModel, repeater, pieceRepeater) {

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
                //if(checkersModelInstance.isPiecePresent(modelIndex)) {

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
                //}
                //else {
                //    console.log("piece not present, no item to center")
                //}
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

function updateCoordinates(checkersModelInstance, fieldRep, pieceRep, fieldWidth, fieldHeight, pieceWidth, pieceHeight,
                           pieceSeparatorX, pieceSeparatorY) {
    var fieldsCoordinates = getCoordinates(fieldRep, fieldWidth, fieldHeight)
    var piecesCoordinates = getPiecesCoordinates(fieldRep, pieceWidth, pieceHeight,  pieceSeparatorX, pieceSeparatorY)
    checkersModelInstance.updateFieldsCoordinates(fieldsCoordinates)
    checkersModelInstance.updatePiecesCoordinates(piecesCoordinates)
}
