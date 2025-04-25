import QtQuick 2.15
import QtQuick.Controls
import checkers.model

Rectangle {
    id: mainMenu
    anchors.fill: parent
    color: "black"
    property alias startGameButton: startGameButton

    Button {
        id: startGameButton
        width: parent.width * 0.2
        height: parent.height * 0.1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter:  parent.verticalCenter
        text: "START GAME"
        onClicked: {
            //root.isMainMenu === true
            root.isMainMenu = !root.isMainMenu
            game.gameOn = true;
            game.player = CheckersModel.Player.white
        }
    }
}
