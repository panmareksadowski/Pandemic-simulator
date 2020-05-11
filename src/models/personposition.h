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

#include <QLineF>
#include <chrono>
#include <random>

class PersonPosition {
  public:
    enum RunStatus { RUN, STOP };

    PersonPosition(std::uniform_real_distribution<double> xDistribution,
                   std::uniform_real_distribution<double> yDistribution, RunStatus runStatus = RUN);

    void move(double distance, const std::vector<QLineF> &obstacles,
              const std::chrono::nanoseconds &time);

    const QPointF &getCordinates() const { return cordinates; }
    const QLineF &getLastMove() const { return lastMove; }

  private:
    using Angle = double;

    static std::tuple<QPointF, Angle>
    calculateNewPositionAfterInteractsWithObstacles(QLineF movingLine, Angle angle,
                                                    const std::vector<QLineF> &obstacles);

    void updateAngle(const std::chrono::nanoseconds &time);

    void normalizeAngle();

    QLineF lastMove; // TODO: use alias for move type
    QPointF cordinates;
    Angle directionAngle; // [0, 360)
    RunStatus runStatus;

    std::chrono::nanoseconds timeOfNextAngelChange;

    static inline std::uniform_real_distribution<Angle> angleGenerator{0, 359.99999};
    static inline std::normal_distribution<> angleChangeGenerator{0, 90};
    static inline std::normal_distribution<> timeOfNextAngleChangeGenerator{
        5 * 60e9, 45e9}; // mean 5 min, deviation 45s
};
