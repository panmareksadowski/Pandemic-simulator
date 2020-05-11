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

#include "simulationstatistics.h"

void SimulationStatistics::updateData(const PersonsList &personsList,
                                      const std::chrono::nanoseconds &duration) {
    recalculateStatistics(personsList);
    this->duration = duration;

    emit dataUpdated();
}

void SimulationStatistics::resetData(int allPersons) {
    this->allPersons = allPersons;
    healthPersons = 0;
    illPersons = 0;
    recoveredPersons = 0;
    deadPersons = 0;

    this->duration = std::chrono::nanoseconds(0);

    emit dataUpdated();
}

void SimulationStatistics::recalculateStatistics(const PersonsList &personsList) {
    healthPersons = 0;
    illPersons = 0;
    recoveredPersons = 0;
    for (const auto &person : personsList) {
        switch (person.getStatus()) {
        case PersonStatus::HEALTH:
            ++healthPersons;
            break;
        case PersonStatus::ILL:
            ++illPersons;
            break;
        case PersonStatus::RECOVERED:
            ++recoveredPersons;
            break;
        }
    }
    deadPersons = allPersons - static_cast<int>(personsList.size());
}

int SimulationStatistics::getAllPersons() const { return allPersons; }

int SimulationStatistics::getAlive() const { return alivePersons; }

int SimulationStatistics::getIll() const { return illPersons; }

int SimulationStatistics::getHealth() const { return healthPersons; }

int SimulationStatistics::getRecovered() const { return recoveredPersons; }

int SimulationStatistics::getDead() const { return deadPersons; }

int SimulationStatistics::getInfected() const { return getAllPersons() - getHealth(); }

std::chrono::minutes::rep SimulationStatistics::getDurationInMinutes() const {
    return std::chrono::duration_cast<std::chrono::minutes>(duration).count();
}
