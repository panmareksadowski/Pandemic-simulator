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

#include "personposition.h"

#include <tuple>

#include "utils/randomgeneretor.hpp"

using std::chrono::nanoseconds;

PersonPosition::PersonPosition(std::uniform_real_distribution<double> xDistribution,
                               std::uniform_real_distribution<double> yDistribution,
                               RunStatus runStatus)
    : cordinates(xDistribution(getRandomGeneretor()), yDistribution(getRandomGeneretor())),
      directionAngle(angleGenerator(getRandomGeneretor())), runStatus(runStatus),
      timeOfNextAngelChange(
          static_cast<nanoseconds::rep>(timeOfNextAngleChangeGenerator(getRandomGeneretor()))) {}

void PersonPosition::move(double distance, const std::vector<QLineF> &obstacles,
                          const std::chrono::nanoseconds &time) {
    if (runStatus == STOP)
        return;

    updateAngle(time);

    QLineF movingLine(getCordinates(), {-1, -1});
    movingLine.setLength(distance);
    movingLine.setAngle(directionAngle);

    std::tie(cordinates, directionAngle) =
        calculateNewPositionAfterInteractsWithObstacles(movingLine, directionAngle, obstacles);
    movingLine.setP2(cordinates);
    lastMove = movingLine;
    normalizeAngle();
}

std::tuple<QPointF, PersonPosition::Angle>
PersonPosition::calculateNewPositionAfterInteractsWithObstacles(
    QLineF movingLine, Angle angle, const std::vector<QLineF> &obstacles) {
    for (const auto &obstacle : obstacles) {
        QPointF intersectionPoint;
        if (movingLine.intersects(obstacle, &intersectionPoint) == QLineF::BoundedIntersection) {
            auto angleTo = movingLine.angleTo(obstacle);
            movingLine.setLength(
                std::max(QLineF(movingLine.p1(), intersectionPoint).length() - 10e9, 0.0));
            if (angleTo >= 180)
                angleTo -= 180;
            if (angleTo <= 90)
                return std::tuple<QPointF, Angle>(movingLine.p2(), angle + 2 * angleTo);
            else
                return std::tuple<QPointF, Angle>(movingLine.p2(), angle - 2 * (180 - angleTo));
        }
    }

    return std::tuple<QPointF, Angle>(movingLine.p2(), angle);
}

void PersonPosition::updateAngle(const nanoseconds &time) {
    if (time > timeOfNextAngelChange) {
        directionAngle += angleChangeGenerator(getRandomGeneretor());
        normalizeAngle();

        timeOfNextAngelChange = time + nanoseconds(static_cast<nanoseconds::rep>(
                                           timeOfNextAngleChangeGenerator(getRandomGeneretor())));
    }
}

void PersonPosition::normalizeAngle() {
    while (directionAngle >= 360)
        directionAngle -= 360;
    while (directionAngle < 0)
        directionAngle += 360;
}
