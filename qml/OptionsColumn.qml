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
import QtQuick.Controls.Material 2.14
import Enums 1.0

Item {
    readonly property alias stoppedPersonsNumber: lockedPersonsSpinBox.value
    readonly property bool canBeHide: !recoveringTimeMetricComboBox.down

    width: 200
    Column {
        anchors.fill: parent

        spacing: 5
        padding: 15

        Label {
            text: "OPTIONS"
            bottomPadding: 10
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            font.pixelSize: 21
            font.bold: true
        }
        Label {
            text: "Locked persons (%):"
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            Material.foreground: AppColors.dirtyWhiteColor
            font.pixelSize: 16
        }
        SpinBox {
            id: lockedPersonsSpinBox
            anchors.horizontalCenter: parent.horizontalCenter
            editable: true
            from: 0
            to: 100
            width: 150
        }
        Label {
            text: "Spread distance (m):"
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Material.foreground: AppColors.dirtyWhiteColor

            font.pixelSize: 16
        }
        SpinBox {
            anchors.horizontalCenter: parent.horizontalCenter
            editable: true
            from: 1
            to: 100
            width: 150
            value: SimulationSettings.propagateDistance
            onValueModified: SimulationSettings.propagateDistance = value
        }
        Label {
            text: "Spread chance (%):"
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Material.foreground: AppColors.dirtyWhiteColor

            font.pixelSize: 16
        }
        SpinBox {
            id: spreadChanceSpinBox
            anchors.horizontalCenter: parent.horizontalCenter
            editable: true
            from: 1
            to: 100 * 100
            stepSize: 10
            width: 150
            property int decimals: 2
            property real realValue: value / 100

            validator: DoubleValidator {
                bottom: Math.min(spreadChanceSpinBox.from,
                                 spreadChanceSpinBox.to)
                top: Math.max(spreadChanceSpinBox.from, spreadChanceSpinBox.to)
            }

            textFromValue: function (value, locale) {
                return Number(value / 100).toLocaleString(locale, 'f', decimals)
            }

            valueFromText: function (text, locale) {
                return Number.fromLocaleString(locale, text) * 100
            }
            value: SimulationSettings.propagateChance * 100
            onValueModified: SimulationSettings.propagateChance = realValue
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Recovering time:"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Material.foreground: AppColors.dirtyWhiteColor

            font.pixelSize: 16
        }
        SpinBox {
            id: recoveringTimeSpinBox
            anchors.horizontalCenter: parent.horizontalCenter
            editable: true
            from: 1
            to: 100000
            width: 150
            value: {
                switch (recoveringTimeMetricComboBox.currentValue) {
                case "Minutes":
                    return SimulationSettings.recoveringTimeInMinutes
                case "Hours":
                    return SimulationSettings.recoveringTimeInHours
                case "Days":
                    return SimulationSettings.recoveringTimeInDays
                default:
                    return 1
                }
            }
            onValueModified: {
                switch (recoveringTimeMetricComboBox.currentValue) {
                case "Minutes":
                    SimulationSettings.recoveringTimeInMinutes = value
                    break
                case "Hours":
                    SimulationSettings.recoveringTimeInHours = value
                    break
                case "Days":
                    SimulationSettings.recoveringTimeInDays = value
                    break
                }
            }
        }
        ComboBox {
            id: recoveringTimeMetricComboBox
            anchors.horizontalCenter: parent.horizontalCenter
            model: ["Minutes", "Hours", "Days"]
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Mortality (%):"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Material.foreground: AppColors.dirtyWhiteColor

            font.pixelSize: 16
        }
        SpinBox {
            id: deadChanceSpinBox
            anchors.horizontalCenter: parent.horizontalCenter
            editable: true
            from: 1
            to: 100
            width: 150
            value: SimulationSettings.deadChance
            onValueModified: SimulationSettings.deadChance = value
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Dot size:"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Material.foreground: AppColors.dirtyWhiteColor

            font.pixelSize: 16
        }
        SpinBox {
            anchors.horizontalCenter: parent.horizontalCenter
            editable: true
            from: 1
            to: 5
            width: 150
            value: SimulationSettings.dotSize
            onValueModified: SimulationSettings.dotSize = value
        }

        ToolSeparator {
            id: separator
            anchors.horizontalCenter: parent.horizontalCenter
            orientation: Qt.Horizontal
            width: parent.width
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            bottomPadding: 10

            text: "TOOLS"
            font.pixelSize: 21
            font.bold: true
        }

        ButtonGroup {
            buttons: drawingTools.children
        }

        Grid {
            id: drawingTools
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 2
            spacing: 0
            padding: 0
            Button {
                text: "LINE"
                width: 80
                spacing: 0
                padding: 0
                topInset: 0
                bottomInset: 0

                onClicked: DrawingToolsController.leftClickSelectedTool = Enums.LINE
            }
            Button {
                text: "RECT"
                width: 80
                spacing: 0

                topInset: 0
                bottomInset: 0
                padding: 0
                onClicked: DrawingToolsController.leftClickSelectedTool = Enums.RECT
            }
            Button {
                text: "RUBBER"
                width: 80
                spacing: 0
                padding: 0

                topInset: 0
                bottomInset: 0
                onClicked: DrawingToolsController.leftClickSelectedTool = Enums.RUBBERRECT
            }
            Button {
                text: "NOTOOL"
                width: 80
                spacing: 0
                padding: 0
                topInset: 0
                bottomInset: 0
                onClicked: DrawingToolsController.leftClickSelectedTool = Enums.NOTOOL
            }
        }
        states: [
            State {
                name: "Started"
                when: Controller.status !== Enums.STOP
                PropertyChanges {
                    target: lockedPersonsSpinBox
                    enabled: false
                }
                PropertyChanges {
                    target: spreadChanceSpinBox
                    enabled: false
                }
                PropertyChanges {
                    target: recoveringTimeSpinBox
                    enabled: false
                }
                PropertyChanges {
                    target: recoveringTimeMetricComboBox
                    enabled: false
                }
                PropertyChanges {
                    target: deadChanceSpinBox
                    enabled: false
                }
            }
        ]
    }
}
