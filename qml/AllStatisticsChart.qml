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
    legend.visible: false
    dropShadowEnabled: true
    antialiasing: false

    PieSeries {
        id: pieSeries
        PieSlice {
            label: "Health"
            value: Statistics.allPersons === 0 ? 1 : Statistics.health
            color: AppColors.healthColor
        }
        PieSlice {
            label: "Recovered"
            value: Statistics.recovered
            color: AppColors.recoveredColor
        }
        PieSlice {
            label: "Ill"
            value: Statistics.ill
            color: AppColors.illColor
        }
        PieSlice {
            label: "Dead"
            value: Statistics.dead
            color: AppColors.deadColor
        }
    }
}
