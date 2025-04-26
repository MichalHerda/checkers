import QtQuick 2.15
import checkers.model

Row {
    id: root

    property double playerTimerWidth: root.width * 0.4
    property double playerTimerHeight: root.height

    PlayerTimer {
        id: playerOneTimer
        width: playerTimerWidth
        height: playerTimerHeight
        playerName: playerOneName
        countdownTimer.running: (game.player === CheckersModel.Player.white)
    }

    Item {
        id: separatorTimer
        width: root.width - (playerTimerWidth * 2)
        height: playerTimerHeight
    }

    PlayerTimer {
        id: playerTwoTimer
        width: playerTimerWidth
        height: playerTimerHeight
        playerName: playerTwoName
        countdownTimer.running: (game.player === CheckersModel.Player.black)
    }
}

