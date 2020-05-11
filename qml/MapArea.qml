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
import QtMultimedia 5.14
import QtQuick.Controls 2.14
import QtQuick.Shapes 1.14
import Enums 1.0

VideoOutput {
    id: videoOutput
    source: VideoSource

    Row {
        z: 10
        anchors.right: videoOutput.right
        anchors.bottom: videoOutput.bottom
        anchors.rightMargin: 20 + videoOutput.width - videoOutput.contentRect.x
                             - videoOutput.contentRect.width
        anchors.bottomMargin: 20 + videoOutput.height - videoOutput.contentRect.y
                              - videoOutput.contentRect.height
        RoundButton {
            id: enlargeMapButton
            width: 60
            height: 60
            radius: 30

            text: "+"
            font.pixelSize: 25
            onClicked: SimulationSettings.enlargeMap()
        }

        RoundButton {
            id: decreasMapButton
            width: 60
            height: 60
            radius: 30

            text: "-"
            font.pixelSize: 25
            onClicked: SimulationSettings.decreaseMap()
        }

        states: [
            State {
                name: "Started"
                when: Controller.status !== Enums.STOP
                PropertyChanges {
                    target: enlargeMapButton
                    enabled: false
                }
                PropertyChanges {
                    target: decreasMapButton
                    enabled: false
                }
            }
        ]
    }

    MouseArea {
        id: mouseArea
        z: 1
        anchors.fill: parent

        property var lastPoint: undefined

        cursorShape: DrawingToolsController.leftClickSelectedTool
                     === Enums.NOTOOL ? Qt.ArrowCursor : Qt.CrossCursor
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPressed: {
            if (lastPoint == undefined)
                lastPoint = Qt.point(mouseX, mouseY)
        }

        onReleased: {
            if (lastPoint != undefined)
                if (mouse.button & Qt.LeftButton)
                    DrawingToolsController.leftClickAction(
                                videoOutput.mapPointToSource(lastPoint),
                                videoOutput.mapPointToSource(Qt.point(mouseX,
                                                                      mouseY)))
                else if ((mouse.button & Qt.RightButton))
                    DrawingToolsController.rightClickAction(
                                videoOutput.mapPointToSource(lastPoint),
                                videoOutput.mapPointToSource(Qt.point(mouseX,
                                                                      mouseY)))

            lastPoint = undefined
        }

        Shape {
            id: drawingLine

            visible: false
            ShapePath {
                strokeColor: "black"
                strokeWidth: 1
                startX: (mouseArea.lastPoint !== undefined) ? mouseArea.lastPoint.x : 0
                startY: (mouseArea.lastPoint !== undefined) ? mouseArea.lastPoint.y : 0
                PathLine {
                    x: mouseArea.mouseX
                    y: mouseArea.mouseY
                }
            }
        }

        RectangleP1P2 {
            id: drawingRect
            visible: false
            color: "transparent"
            p1: mouseArea.lastPoint !== undefined ? mouseArea.lastPoint : Qt.point(
                                                        0, 0)
            p2: Qt.point(mouseArea.mouseX, mouseArea.mouseY)
        }

        states: [
            State {
                name: "Line"
                when: DrawingToolsController.leftClickSelectedTool === Enums.LINE
                      && (mouseArea.pressedButtons & Qt.LeftButton)
                PropertyChanges {
                    target: drawingLine
                    visible: true
                }
                PropertyChanges {
                    target: drawingRect
                    visible: false
                }
            },
            State {
                name: "RECT"
                when: DrawingToolsController.leftClickSelectedTool === Enums.RECT
                      && (mouseArea.pressedButtons & Qt.LeftButton)
                PropertyChanges {
                    target: drawingLine
                    visible: false
                }
                PropertyChanges {
                    target: drawingRect
                    visible: true
                    border.color: "black"
                }
            },
            State {
                name: "RUBBERRECT"
                when: DrawingToolsController.leftClickSelectedTool === Enums.RUBBERRECT
                      && (mouseArea.pressedButtons & Qt.LeftButton)
                      || (mouseArea.pressedButtons === Qt.RightButton)
                PropertyChanges {
                    target: drawingLine
                    visible: false
                }
                PropertyChanges {
                    target: drawingRect
                    visible: true
                    border.color: "red"
                }
            }
        ]
    }
}
