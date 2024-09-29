import QtQuick 2.15

Item {
    id: gameBoard
    property alias checkersModelInstance: checkersModelInstance

    Grid {
        anchors.fill: parent
        columns: checkersModelInstance.columns

    }
}
