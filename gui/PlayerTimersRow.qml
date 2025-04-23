import QtQuick 2.15

Item {
    Row {
        id: root
        property double horizontalSpacing: root.width * 0.1
        property double playerTimerWidth: root.width * 0.35
        property double playerTimerHeight: root.height * 0.75

        spacing: horizontalSpacing


        PlayerTimer {
            id: playerOneTimer
            width: playerTimerWidth
            height: playerTimerHeight
        }

        PlayerTimer {
            id: playerTwoTimer
            width: playerTimerWidth
            height: playerTimerHeight
        }
    }
}
