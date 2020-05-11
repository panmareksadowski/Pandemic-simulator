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

#include "simulationexecutor.h"

using std::chrono_literals::operator""ns;

SimulationExecutor::SimulationExecutor(const Map &map, SimulationSettings &settings)
    : map(map), settings(settings), recoveredPersonsMarker(personsList),
      deadPersonsRemover(personsList), personsMoveController(duration, personsList, map, settings) {
    start();
}

SimulationExecutor::~SimulationExecutor() {
    finishThread = true;
    wait();
}

void SimulationExecutor::play(int numberOfRunPersons, int numberOfStoppedPersons) {
    if (this->status == Enums::STOP) {
        personsList.add(numberOfRunPersons, numberOfStoppedPersons, map, settings);
        recoveredPersonsMarker.reset(settings.getRecoveringTime() / 201);
        deadPersonsRemover.reset(settings.getRecoveringTime() / 199);
    }
    status = Enums::PLAY;
}

void SimulationExecutor::pause() { status = Enums::PAUSE; }

void SimulationExecutor::stop() {
    status = Enums::STOP;
    personsList.clear();
    resetDuration();
}

void SimulationExecutor::resetDuration() { duration = 0ns; }

PersonsList SimulationExecutor::getPersonsList() const { return personsList; }

std::chrono::nanoseconds SimulationExecutor::getDuration() const { return duration; }

void SimulationExecutor::run() {
    while (not finishThread) {
        if (status != Enums::PLAY) {
            QThread::msleep(500);
            markLastTick();
            continue;
        }
        auto elapsedTimeFromLastTick = getElapsedTimeFromLastTickAndMarkLastTick();
        duration += settings.getAcceleretion() * elapsedTimeFromLastTick;
        tick(elapsedTimeFromLastTick);
    }
}

void SimulationExecutor::tick(const std::chrono::nanoseconds &elapsedFromLastTick) {
    deadPersonsRemover.removeDeadPersons(duration);
    recoveredPersonsMarker.markRecoveredPersons(duration);
    personsMoveController.tick(elapsedFromLastTick);
}

void SimulationExecutor::markLastTick() { lastTickTime = std::chrono::steady_clock::now(); }

std::chrono::nanoseconds SimulationExecutor::getElapsedTimeFromLastTickAndMarkLastTick() {
    auto now = std::chrono::steady_clock::now();
    auto ret = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastTickTime);
    lastTickTime = now;
    return ret;
}
