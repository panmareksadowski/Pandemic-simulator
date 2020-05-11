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
    property var expandedArea

    width: 200
    z: 2

    AllStatisticsChart {
        id: chart1
        x: chart1SlotArea.x
        y: chart1SlotArea.y
        width: chart1SlotArea.width
        height: chart1SlotArea.height

        ToolTip {
            anchors.centerIn: parent

            delay: 1000
            timeout: 2000
            visible: chart1MouseArea.containsMouse
            text: chart1MouseArea.isPermanentlyExtended ? "Double click to minimize" : "Press and hold or double click to expand"
        }

        MouseArea {
            id: chart1MouseArea
            anchors.fill: parent

            property bool isPermanentlyExtended: false
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true
            onDoubleClicked: isPermanentlyExtended = !isPermanentlyExtended
        }

        states: State {
            name: "extend"
            when: chart1MouseArea.pressed
                  || chart1MouseArea.isPermanentlyExtended
            PropertyChanges {
                target: chart1
                x: expandedArea.x
                y: expandedArea.y
                width: expandedArea.width
                height: expandedArea.height
                z: 3
                legend.visible: true
            }
        }

        transitions: Transition {
            SequentialAnimation {
                PauseAnimation {
                    duration: 80
                }
                PropertyAnimation {
                    properties: "x,y, width, height, z"
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    StatisticsChart {
        id: chart2
        x: chart2SlotArea.x
        y: chart2SlotArea.y
        width: chart2SlotArea.width
        height: chart2SlotArea.height
        isExtended: false

        downStatistics: [
            StatisticInfo {
                name: "Ill"
                color: AppColors.illColor
                value: Statistics.ill
            }
        ]
        upStatistics: [
            StatisticInfo {
                name: "Recover"
                color: AppColors.recoveredColor
                value: Statistics.recovered
            },
            StatisticInfo {
                name: "Dead"
                color: AppColors.deadColor
                value: Statistics.dead
            }
        ]

        ToolTip {
            anchors.centerIn: parent

            delay: 1000
            timeout: 2000
            visible: chart2tMouseArea.containsMouse
            text: chart2tMouseArea.isPermanentlyExtended ? "Double click to minimize" : "Press and hold or double click to expand"
        }

        MouseArea {
            id: chart2tMouseArea
            anchors.fill: parent

            property bool isPermanentlyExtended: false
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true
            onDoubleClicked: isPermanentlyExtended = !isPermanentlyExtended
        }

        states: State {
            name: "extend"
            when: chart2tMouseArea.pressed
                  || chart2tMouseArea.isPermanentlyExtended
            PropertyChanges {
                target: chart2
                x: expandedArea.x
                y: expandedArea.y
                width: expandedArea.width
                height: expandedArea.height
                z: 3
                isExtended: true
            }
        }

        transitions: Transition {
            SequentialAnimation {
                PauseAnimation {
                    duration: 80
                }
                PropertyAnimation {
                    properties: "x,y, width, height, z"
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    StatisticsChart {
        id: chart3
        x: chart3SlotArea.x
        y: chart3SlotArea.y
        width: chart3SlotArea.width
        height: chart3SlotArea.height
        isExtended: false

        downStatistics: [
            StatisticInfo {
                name: "Health+Recovered"
                color: AppColors.healthColor
                value: Statistics.health + Statistics.recovered
            }
        ]
        upStatistics: [
            StatisticInfo {
                name: "Ill+Dead"
                color: AppColors.illColor
                value: Statistics.ill + Statistics.dead
            }
        ]

        ToolTip {
            anchors.centerIn: parent

            delay: 1000
            timeout: 2000
            visible: chart3MouseArea.containsMouse
            text: chart3MouseArea.isPermanentlyExtended ? "Double click to minimize" : "Press and hold or double click to expand"
        }

        MouseArea {
            id: chart3MouseArea
            anchors.fill: parent

            property bool isPermanentlyExtended: false
            acceptedButtons: Qt.LeftButton
            hoverEnabled: true
            onDoubleClicked: isPermanentlyExtended = !isPermanentlyExtended
        }

        states: State {
            name: "extend"
            when: chart3MouseArea.pressed
                  || chart3MouseArea.isPermanentlyExtended
            PropertyChanges {
                target: chart3
                x: expandedArea.x
                y: expandedArea.y
                width: expandedArea.width
                height: expandedArea.height
                z: 3
                isExtended: true
            }
        }
        transitions: Transition {
            SequentialAnimation {
                PauseAnimation {
                    duration: 80
                }
                PropertyAnimation {
                    properties: "x,y, width, height, z"
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    Column {
        anchors.fill: parent

        spacing: 5
        topPadding: 50
        padding: 5

        Label {
            text: "STATISTICS"

            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            bottomPadding: 10

            font.pixelSize: 21
            font.bold: true
        }

        Item {
            id: chart1SlotArea
            width: parent.width
            height: 200
        }

        Item {
            id: chart2SlotArea
            width: parent.width
            height: 200
        }

        Item {
            id: chart3SlotArea
            width: parent.width
            height: 200
        }
    }
}
