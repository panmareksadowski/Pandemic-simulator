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

#include "simulationcontroller.h"

#include "models/map.h"
#include "models/simulationsettings.h"
#include "models/simulationstatistics.h"
#include "simulationdrawer.h"
#include "simulationexecutor.h"

SimulationController::SimulationController(const Map &map,
                                           const SimulationSettings &simulationSettings,
                                           SimulationExecutor &simulationExecutor,
                                           SimulationDrawer &simulationDrawer,
                                           SimulationStatistics &simulationStatisctics)
    : map(map), simulationSettings(simulationSettings), simulationExecutor(simulationExecutor),
      simulationDrawer(simulationDrawer), simulationStatisctics(simulationStatisctics) {
    connect(&refreshTimer, &QTimer::timeout, this, &SimulationController::refresh);
    refreshTimer.start(50);
}

void SimulationController::play(int numberOfPersons, int percentStoppedPersons) {
    if (status != Enums::PLAY) {
        if (status == Enums::STOP)
            simulationStatisctics.resetData(numberOfPersons);
        status = Enums::PLAY;
        int stoppedPersonsNumber = numberOfPersons * percentStoppedPersons / 100;
        simulationExecutor.play(numberOfPersons - stoppedPersonsNumber, stoppedPersonsNumber);
        emit changedStatus();
    };
}

void SimulationController::pause() {
    if (status == Enums::PLAY) {
        status = Enums::PAUSE;
        simulationExecutor.pause();
        emit changedStatus();
    }
}

void SimulationController::stop() {
    status = Enums::STOP;
    simulationStatisctics.resetData();
    simulationExecutor.stop();

    emit changedStatus();
}

Enums::ControllerStatus SimulationController::getStatus() { return status; }

void SimulationController::refresh() {
    auto personsList = simulationExecutor.getPersonsList();
    simulationStatisctics.updateData(personsList, simulationExecutor.getDuration());
    simulationDrawer.draw(map, personsList, simulationSettings);
}
