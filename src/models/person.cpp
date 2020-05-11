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

#include "person.h"

#include <chrono>
#include <tuple>

#include <QLineF>

#include "utils/randomgeneretor.hpp"

using namespace std::chrono_literals;
using std::chrono::nanoseconds;

Person Person::createHealthPerson(std::uniform_real_distribution<double> xDistribution,
                                  std::uniform_real_distribution<double> yDistribution,
                                  PersonPosition::RunStatus runStatus) {
    return Person(PersonPosition(xDistribution, yDistribution, runStatus),
                  PersonStatus::createHealthStatus());
}

Person Person::createIllPerson(std::uniform_real_distribution<double> xDistribution,
                               std::uniform_real_distribution<double> yDistribution,
                               double deadChance, const nanoseconds &averageRecoveringTime,
                               PersonPosition::RunStatus runStatus) {
    return Person(PersonPosition(xDistribution, yDistribution, runStatus),
                  PersonStatus::createIllStatus(deadChance, averageRecoveringTime));
}

Person::Person(PersonPosition position, PersonStatus status)
    : position(std::move(position)), status(std::move(status)) {}

void Person::move(double distance, const std::vector<QLineF> &obstacles,
                  const std::chrono::nanoseconds &time) {
    position.move(distance, obstacles, time);
}

void Person::updateRecoverStatus(const std::chrono::nanoseconds &time) {
    status.updateRecoverStatus(time);
}

void Person::meetWithIllPerson(double deadChance, double propagateChance,
                               const std::chrono::nanoseconds &time,
                               const std::chrono::nanoseconds &averageRecoveringTime) {
    status.meetWithIllPerson(deadChance, propagateChance, time, averageRecoveringTime);
}

bool Person::isDead(const std::chrono::nanoseconds &time) const { return status.isDead(time); }
