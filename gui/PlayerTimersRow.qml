import QtQuick 2.15
import checkers.model
import Checkers 1.0

Row {
    id: root

    property double playerTimerWidth: root.width * 0.4
    property double playerTimerHeight: root.height

    PlayerTimer {
        id: playerOneTimer
        width: playerTimerWidth
        height: playerTimerHeight
        playerName: playerOneName
        countdownTimer.running: (checkersModelInstance.player === CheckersModel.Player.white)
        nameRect.border.color: (checkersModelInstance.player === CheckersModel.Player.white) ? CheckersTheme.uiBorderColor : "blue"
        timeRect.border.color: (checkersModelInstance.player === CheckersModel.Player.white) ? CheckersTheme.uiBorderColor : "blue"
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
        countdownTimer.running: (checkersModelInstance.player === CheckersModel.Player.black)
        nameRect.border.color: (checkersModelInstance.player === CheckersModel.Player.black) ? CheckersTheme.uiBorderColor : "blue"
        timeRect.border.color: (checkersModelInstance.player === CheckersModel.Player.black) ? CheckersTheme.uiBorderColor : "blue"
    }
}

