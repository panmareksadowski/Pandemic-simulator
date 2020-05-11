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

#include "personsmovecontroller.h"

#include <QtConcurrent>

#include "models/map.h"
#include "models/person.h"
#include "models/personslist.h"
#include "models/simulationsettings.h"
#include "utils/geometry.hpp"

PersonsMoveController::PersonsMoveController(const std::chrono::nanoseconds &duration,
                                             PersonsList &personsList, const Map &map,
                                             SimulationSettings &settings)
    : duration(duration), personsList(personsList), map(map), settings(settings) {}

void PersonsMoveController::tick(const std::chrono::nanoseconds &elapsedFromLastTick) {
    auto [illPersonsMovement, healthPersonsMovements] = movePersons(elapsedFromLastTick);
    propagateIllStatus(illPersonsMovement, healthPersonsMovements);
}

std::tuple<std::vector<QLineF>, std::vector<std::tuple<QLineF, Person *>>>
PersonsMoveController::movePersons(const std::chrono::nanoseconds &elapsedFromLastTick) {
    double distance =
        settings.getDistancePerElapsedTime(elapsedFromLastTick, SimulationSettings::PIXELS);
    if (distance > 0.85 * std::min(map.getWidth(), map.getHeight()))
        settings.forceDecreaseAcceleretion(0.85 * std::min(map.getWidth(), map.getHeight()) /
                                           distance);

    std::vector<QLineF> illPersonsMovement;
    std::vector<std::tuple<QLineF, Person *>> healthPersonsMovement;
    for (auto &person : personsList) {
        QPointF p1 = person.getCordinates();
        person.move(distance, map.getObstacles(), duration);
        if (person.getStatus() == PersonStatus::ILL)
            illPersonsMovement.emplace_back(p1, person.getCordinates());
        else if (person.getStatus() == PersonStatus::HEALTH) {
            healthPersonsMovement.emplace_back(QLineF{p1, person.getCordinates()}, &person);
        }
    }
    return std::tuple<std::vector<QLineF>, std::vector<std::tuple<QLineF, Person *>>>{
        std::move(illPersonsMovement), std::move(healthPersonsMovement)};
}

void PersonsMoveController::propagateIllStatus(
    const std::vector<QLineF> &illPersonsMovements,
    const std::vector<std::tuple<QLineF, Person *>> &healthPersonsMovements) {
    if (illPersonsMovements.empty() || healthPersonsMovements.empty())
        return;

    double maxPropagateDistance = settings.getPropagateDistance(SimulationSettings::PIXELS);
    QtConcurrent::blockingMap(healthPersonsMovements, [&](const auto &healthPersonMovment) {
        const auto &[healthPersonMove, healthPerson] = healthPersonMovment;
        for (const auto &illPersonMove : illPersonsMovements)
            if (nearestDistance(illPersonMove, healthPersonMove) <= maxPropagateDistance)
                healthPerson->meetWithIllPerson(settings.getDeadChance(),
                                                settings.getPropagateChance(), duration,
                                                settings.getRecoveringTime());
    });
}
