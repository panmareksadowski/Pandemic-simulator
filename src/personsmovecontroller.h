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
#include <tuple>
#include <vector>

#include <QLineF>

class Map;
class Person;
class PersonsList;
class SimulationSettings;

class PersonsMoveController {
  public:
    PersonsMoveController(const std::chrono::nanoseconds &duration, PersonsList &personsList,
                          const Map &map, SimulationSettings &settings);

    void tick(const std::chrono::nanoseconds &elapsedFromLastTick);

  private:
    // TODO: use alias for that obscure type
    std::tuple<std::vector<QLineF>, std::vector<std::tuple<QLineF, Person *>>>
    movePersons(const std::chrono::nanoseconds &elapsedFromLastTick);
    void
    propagateIllStatus(const std::vector<QLineF> &illPersonsMovement,
                       const std::vector<std::tuple<QLineF, Person *>> &healthPersonsMovements);

    const std::chrono::nanoseconds &duration;
    PersonsList &personsList;
    const Map &map;
    SimulationSettings &settings;
};
