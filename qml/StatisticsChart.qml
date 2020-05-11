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
import QtCharts 2.14
import Enums 1.0

ChartView {
    property bool isExtended

    property list<StatisticInfo> downStatistics
    property list<StatisticInfo> upStatistics

    legend.visible: isExtended
    antialiasing: false

    ValueAxis {
        id: axisX
        property int lastMinute: 0
        min: 0
        max: Math.max(lastMinute + 10, 60)

        labelFormat: "%d"
        labelsFont.pixelSize: isExtended ? 16 : 8
        titleText: "min"
        titleFont.pixelSize: isExtended ? 16 : 8
        visible: isExtended
    }

    ValueAxis {
        id: axisY
        min: 0
        max: Statistics.allPersons > 0 ? Statistics.allPersons : 1
        labelsFont.pixelSize: isExtended ? 16 : 8
        labelFormat: "%d"
    }

    Component.onCompleted: {
        initDownStatistics()
        initUpStatistics()
    }

    Connections {
        id: dataUpdater
        target: Statistics
        property bool finished: false
        onDataUpdated: {
            if (finished)
                return

            axisX.lastMinute = Statistics.durationMinutes
            updateDownStatistics()
            updateUpStatistics()

            if (Controller.status !== Enums.STOP && Statistics.ill === 0)
                finished = true
        }
    }

    Connections {
        target: Controller
        onChangedStatus: {
            if (Controller.status === Enums.STOP) {
                clearDownStatistics()
                clearUpStatistics()
                dataUpdater.finished = false
            }
        }
    }

    function initDownStatistics() {
        for (var i = 0; i < downStatistics.length; i++) {
            var downSerie = createSeries(ChartView.SeriesTypeArea,
                                         downStatistics[i].name, axisX, axisY)
            downSerie.color = downStatistics[i].color
        }
    }

    function initUpStatistics() {
        for (var i = 0; i < upStatistics.length; i++) {
            var upSerie = createSeries(ChartView.SeriesTypeArea,
                                       upStatistics[i].name, axisX, axisY)
            upSerie.color = upStatistics[i].color
            upSerie.lowerSeries = Qt.createQmlObject(
                        'import QtCharts 2.14; LineSeries {}', upSerie)
        }
    }

    function updateDownStatistics() {

        for (var i = 0; i < downStatistics.length; i++) {
            var downSerie = series(downStatistics[i].name)
            downSerie.upperSeries.append(Statistics.durationMinutes,
                                         downStatistics[i].value)
        }
    }

    function updateUpStatistics() {
        for (var i = 0; i < upStatistics.length; i++) {
            var upSerie = series(upStatistics[i].name)
            upSerie.upperSeries.append(Statistics.durationMinutes,
                                       Statistics.allPersons)
            upSerie.lowerSeries.append(
                        Statistics.durationMinutes,
                        Statistics.allPersons - upStatistics[i].value)
        }
    }

    function clearDownStatistics() {
        for (var i = 0; i < downStatistics.length; i++) {
            var downSerie = series(downStatistics[i].name)
            downSerie.upperSeries.clear()
        }
    }

    function clearUpStatistics() {
        for (var i = 0; i < upStatistics.length; i++) {
            var upSerie = series(upStatistics[i].name)
            upSerie.upperSeries.clear()
            upSerie.lowerSeries.clear()
        }
    }
}
