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
 *****************************************************************************/ import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    height: 30

    Row {
        anchors.centerIn: parent
        spacing: 15
        padding: 5

        Label {
            text: "Total: " + Statistics.allPersons
            color: AppColors.dirtyWhiteColor
            font.pixelSize: 16
            font.bold: true
        }

        Label {
            text: "Alive: " + Statistics.alive
            color: AppColors.aliveColor
            font.pixelSize: 16
            font.bold: true
        }

        Label {
            text: "Health: " + Statistics.health
            color: AppColors.healthColor
            font.pixelSize: 16
            font.bold: true
        }

        Label {
            text: "Recovered: " + Statistics.recovered
            color: AppColors.recoveredColor
            font.bold: true
            font.pixelSize: 16
        }

        Label {
            text: "Ill: " + Statistics.ill
            color: AppColors.illColor
            font.pixelSize: 16
            font.bold: true
        }

        Label {
            text: "Dead: " + Statistics.dead
            color: AppColors.deadColor
            font.pixelSize: 16
            font.bold: true
        }

        Label {
            text: "Total infected: " + Statistics.infected
            color: AppColors.infectedColor
            font.pixelSize: 16
            font.bold: true
        }
    }
}
