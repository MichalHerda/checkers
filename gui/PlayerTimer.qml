import QtQuick 2.15
import QtQuick.Controls
import Checkers 1.0

Item {
    id: root
    property string playerName: "Player "
    property int countdown: 180
    property alias countdownTimer: countdownTimer
    property alias name: name.text

    signal timeout()

    Column {
        id: column
        anchors.fill: parent

        Rectangle {
            id: nameRect
            color: CheckersTheme.backgroundColor
            border {
                width: parent.width * 0.005
                color: CheckersTheme.uiBorderColor
            }

            width: column.width
            height: column.height * 0.5

            Label {
                id: name
                anchors.fill: parent
                text: root.playerName
                horizontalAlignment: "AlignHCenter"
                font.bold: true
                font.pointSize: 16
                color: "white"
            }
        }

        Rectangle {
            id: timeRect
            color: CheckersTheme.backgroundColor
            border {
                width: parent.width * 0.005
                color: CheckersTheme.uiBorderColor
            }
            width: column.width
            height: column.height * 0.5

            Row {
                id: timerRow
                anchors.fill: parent

                Label {
                    id: minutesText
                    width: parent.width * 0.4
                    height: parent.height
                    text: Math.floor(root.countdown / 60).toString().padStart(2, "0")
                    horizontalAlignment: "AlignHCenter"
                    font.pointSize: 14
                    color: countdown <= 3 ? "red" : "white"
                }

                Label {
                    id: colonText
                    width: parent.width * 0.2
                    height: parent.height
                    text: ":"
                    horizontalAlignment: "AlignHCenter"
                    font.pointSize: 14
                    color: countdown <= 3 ? "red" : "white"
                }

                Label {
                    id: secondsText
                    width: parent.width * 0.4
                    height: parent.height
                    text: (root.countdown % 60).toString().padStart(2, "0")
                    horizontalAlignment: "AlignHCenter"
                    font.pointSize: 14
                    color: countdown <= 3 ? "red" : "white"
                }
            }
        }
    }

    Timer {
        id: countdownTimer
        interval: 1000
        //running: game.gameOn
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

    Connections {
        id: countdownTimerConnection
        target: game
         function onGameOnChanged() {
            console.log("GAME ON CHANGED !!!")
            if (game.gameOn) {
                countdownTimer.start()
            } else {
                countdownTimer.stop()
            }
        }
    }

}
