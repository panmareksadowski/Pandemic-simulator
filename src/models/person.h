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

#include "personposition.h"
#include "personstatus.h"

class Person {
  public:
    static Person createHealthPerson(std::uniform_real_distribution<double> xDistribution,
                                     std::uniform_real_distribution<double> yDistribution,
                                     PersonPosition::RunStatus runStatus = PersonPosition::RUN);
    static Person createIllPerson(std::uniform_real_distribution<double> xDistribution,
                                  std::uniform_real_distribution<double> yDistribution,
                                  double deadChance,
                                  const std::chrono::nanoseconds &averageRecoveringTime,
                                  PersonPosition::RunStatus runStatus = PersonPosition::RUN);

    void move(double distance, const std::vector<QLineF> &obstacles,
              const std::chrono::nanoseconds &time);

    const QLineF &getLastMove() const { return position.getLastMove(); }

    void updateRecoverStatus(const std::chrono::nanoseconds &averageRecoveringTime);

    void meetWithIllPerson(double deadChance, double propagateChance,
                           const std::chrono::nanoseconds &time,
                           const std::chrono::nanoseconds &averageRecoveringTime);

    const QPointF &getCordinates() const { return position.getCordinates(); }

    PersonStatus::Status getStatus() const { return status.getStatus(); }

    bool isDead(const std::chrono::nanoseconds &duration) const;

  private:
    Person(PersonPosition position, PersonStatus status);

    PersonPosition position; // TODO: use pimpl
    PersonStatus status;
};
