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

#pragma once

#include <chrono>
#include <vector>

#include <QReadWriteLock>

#include "map.h"
#include "person.h"
#include "simulationsettings.h"

class PersonsList : protected std::vector<Person> {
  public:
    PersonsList() = default;
    PersonsList(const PersonsList &other);
    PersonsList &operator=(const PersonsList &other);

    void clear();
    void add(int numberOfRunPersons, int numberOfStoppedPersons, const Map &map,
             const SimulationSettings &settings);
    void removeDeadPersons(const std::chrono::nanoseconds &duration);
    void markRecoveredPersons(const std::chrono::nanoseconds &duration);

    using std::vector<Person>::begin;
    using std::vector<Person>::end;
    using std::vector<Person>::size;

  private:
    mutable QReadWriteLock personsListLock;
};
