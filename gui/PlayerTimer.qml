import QtQuick 2.15


// PlayerTimer.qml
Item {
    id: root
    property string playerName: "Player "
    property int countdown: 60
    property alias countdownTimer: countdownTimer
    property alias name: name.text

    signal timeout()

    Column {
        id: column
        spacing: root.height * 0.1

        Text {
            id: name
            text: root.playerName
            font.bold: true
            font.pointSize: 16
            color: "white"
        }

        Text {
            id: timerText
            text: countdown.toString()
            font.pointSize: 14
            color: countdown <= 3 ? "red" : "white"
        }
    }

    Timer {
        id: countdownTimer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            if (root.countdown > 0) {
                root.countdown--
            } else {
                countdownTimer.stop()
                root.timeout()
            }
        }
    }
}
