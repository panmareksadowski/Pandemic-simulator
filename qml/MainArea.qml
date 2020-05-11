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

Item {

    Item {
        id: mainArea

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: controlBar.top

        StatisticsBar {
            id: topRow
            anchors.top: parent.top
            anchors.left: leftColumn.right
            anchors.right: options.left
        }

        StatisticsColumn {
            id: leftColumn
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left

            expandedArea: mainArea
        }

        MapArea {
            id: mapArea
            anchors.top: topRow.bottom
            anchors.bottom: parent.bottom
            anchors.left: leftColumn.right
            anchors.right: options.left
        }

        ToolTip {
            id: expandOptionsToolTip
            x: options.x
            y: mapArea.y + 0.2 * mapArea.height
            height: 90

            timeout: 15000
            visible: !AppSettings.skipExpandOptionsHint
            text: "Hint: Move the cursor to the right screen edge to expand options panel ->"
            font.pixelSize: 17
            Button {
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                text: "Don't show this hint again"
                font.pixelSize: 12
                onClicked: AppSettings.skipExpandOptionsHint = true
            }
        }

        OptionsColumn {
            id: options
            anchors.topMargin: 50
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            x: parent.width - 10

            MouseArea {
                id: optionsMouseArea
                anchors.fill: parent

                acceptedButtons: Qt.NoButton
                hoverEnabled: true
            }

            states: State {
                name: "exposed"
                when: optionsMouseArea.containsMouse || !options.canBeHide
                PropertyChanges {
                    target: options
                    x: parent.width - 200
                }
                PropertyChanges {
                    target: expandOptionsToolTip
                    visible: false
                    restoreEntryValues: false
                }
            }

            transitions: Transition {
                PropertyAnimation {
                    properties: "x"
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    ControlBar {
        id: controlBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        onPlay: Controller.play(personsNumber, options.stoppedPersonsNumber)
    }

    Button {
        text: "About"
        onClicked: aboutDialog.open()
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: controlBar.verticalCenter
    }

    AboutDialog {
        id: aboutDialog
        anchors.centerIn: parent
    }
}
