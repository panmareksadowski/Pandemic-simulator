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

#include "personslist.h"

PersonsList::PersonsList(const PersonsList &other) : std::vector<Person>() {
    QWriteLocker locker(&other.personsListLock);
    std::vector<Person>::operator=(other);
}

PersonsList &PersonsList::operator=(const PersonsList &other) {
    if (this != &other) {
        QWriteLocker locker(&other.personsListLock);
        std::vector<Person>::operator=(other);
    }
    return *this;
}

void PersonsList::clear() {
    QWriteLocker locker(&personsListLock);
    std::vector<Person>::clear();
}

void PersonsList::add(int numberOfRunPersons, int numberOfStoppedPersons, const Map &map,
                      const SimulationSettings &settings) {
    QWriteLocker locker(&personsListLock);
    reserve(size() + static_cast<size_t>(numberOfRunPersons) +
            +static_cast<size_t>(numberOfStoppedPersons));

    push_back(Person::createIllPerson(map.getXDistribution(), map.getYDistribution(),
                                      settings.getDeadChance(), settings.getRecoveringTime()));
    for (int i = 1; i < numberOfRunPersons; ++i)
        push_back(Person::createHealthPerson(map.getXDistribution(), map.getYDistribution()));
    for (int i = 0; i < numberOfStoppedPersons; ++i)
        push_back(Person::createHealthPerson(map.getXDistribution(), map.getYDistribution(),
                                             PersonPosition::STOP));
}

void PersonsList::removeDeadPersons(const std::chrono::nanoseconds &duration) {
    QWriteLocker locker(&personsListLock);
    auto end = std::remove_if(this->begin(), this->end(),
                              [&duration](const auto &person) { return person.isDead(duration); });

    erase(end, this->end());
}

void PersonsList::markRecoveredPersons(const std::chrono::nanoseconds &duration) {
    for (auto &person : *this)
        person.updateRecoverStatus(duration);
}
