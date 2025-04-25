import QtQuick 2.15
import checkers.model

Row {
    id: root
    //anchors.fill: parent

    //property double horizontalSpacing: parent.width * 0.1
    //property double playerTimerWidth: parent.width * 0.35
    //property double playerTimerHeight: parent.height * 0.75

    PlayerTimer {
        id: playerOneTimer
        //x: horizontalSpacing
        width: root.width * 0.5 //playerTimerWidth
        height: root.height //playerTimerHeight
        playerName: playerOneName
        countdownTimer.running: (game.player === CheckersModel.Player.white)
    }

    PlayerTimer {
        id: playerTwoTimer
        //x: ( horizontalSpacing * 5 ) + playerTimerWidth
        width: root.width * 0.5 //playerTimerWidth
        height: root.height //playerTimerHeight
        playerName: playerTwoName
        countdownTimer.running: (game.player === CheckersModel.Player.black)
    }
}

