// Copyright 2020 Marek Sadowski


/******************************************************************************
 * This file is part of Pandemic-simulator.
 * Pandemic-simulator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Pandemic-simulator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Pandemic-simulator.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
import QtQuick 2.14
import QtQuick.Controls 2.14
import Enums 1.0

Item {
    signal play
    readonly property alias personsNumber: personsNumberSpinBox.value

    height: 50

    Row {
        anchors.centerIn: parent

        Label {
            text: "Time: " + String(
                      Math.trunc(Statistics.durationMinutes / 60)).padStart(
                      2, '0') + ":" + String(
                      Statistics.durationMinutes % 60).padStart(2, '0')
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 21
            height: parent.height
        }

        Label {
            text: "Population:"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            leftPadding: 30
            font.pixelSize: 21
            height: parent.height
        }

        SpinBox {
            id: personsNumberSpinBox
            editable: true
            from: 1
            to: 10000
            value: 100
            width: 150
        }

        Button {
            id: playButton
            text: "Play"
            onPressed: play()
            width: 70
        }

        Button {
            id: pauseButton
            text: "Pause"
            onPressed: Controller.pause()
            width: 70
        }

        Button {
            id: stopButton
            text: "Stop"
            onPressed: Controller.stop()
            width: 70
        }

        Label {
            text: "Speed:"
            leftPadding: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 19
            height: parent.height
        }

        SpinBox {
            id: timesAcceleretionSpinBox
            editable: true
            from: 1
            to: 10000
            stepSize: {
                if (SimulationSettings.acceleration < 10)
                    1
                else if (SimulationSettings.acceleration < 50)
                    5
                else if (SimulationSettings.acceleration < 100)
                    10
                else if (SimulationSettings.acceleration < 1000)
                    25
                else
                    100
            }
            Label {
                text: "x"
                anchors.right: timesAcceleretionSpinBox.contentItem.left
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 14
                height: parent.height
            }
            value: SimulationSettings.acceleration
            width: 150
            onValueModified: SimulationSettings.acceleration = value
        }

        Label {
            id: warningSpeedLabel
            text: "WARNING: Speed decreased!"
            leftPadding: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 19
            height: parent.height
            color: AppColors.warningColor
            visible: false
            Connections {
                target: SimulationSettings
                onAccelleretionDecresed: {
                    warningSpeedLabel.visible = true
                    warningVisibilityDisablerTimer.start()
                }
            }

            Timer {
                id: warningVisibilityDisablerTimer
                interval: 2500
                running: false
                repeat: false
                onTriggered: warningSpeedLabel.visible = false
            }
        }
    }

    states: [
        State {
            name: "Started"
            when: Controller.status === Enums.PLAY
            PropertyChanges {
                target: playButton
                enabled: false
            }
            PropertyChanges {
                target: personsNumberSpinBox
                enabled: false
            }
        },
        State {
            name: "Paused"
            when: Controller.status === Enums.PAUSE
            PropertyChanges {
                target: pauseButton
                enabled: false
            }
            PropertyChanges {
                target: personsNumberSpinBox
                enabled: false
            }
        },
        State {
            name: "Stopped"
            when: Controller.status === Enums.STOP
            PropertyChanges {
                target: pauseButton
                enabled: false
            }
            PropertyChanges {
                target: stopButton
                enabled: false
            }
        }
    ]
}
