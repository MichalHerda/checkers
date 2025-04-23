import QtQuick 2.15

Row {
    id: root

    property double horizontalSpacing: root.width * 0.1
    property double playerTimerWidth: root.width * 0.35
    property double playerTimerHeight: root.height * 0.75

    PlayerTimer {
        id: playerOneTimer
        x: horizontalSpacing
        width: playerTimerWidth
        height: playerTimerHeight
        playerName: playerOneName
    }

    PlayerTimer {
        id: playerTwoTimer
        x: ( horizontalSpacing * 5 ) + playerTimerWidth
        width: playerTimerWidth
        height: playerTimerHeight
        playerName: playerTwoName
    }
}

