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

#include "map.h"

#include <QRectF>

Map::Map(int width, int height)
    : width(width), height(height),
      obstacles(
          {{0, 0, static_cast<double>(width), 0},
           {static_cast<double>(width), 0, static_cast<double>(width), static_cast<double>(height)},
           {static_cast<double>(width), static_cast<double>(height), 0,
            static_cast<double>(height)},
           {0, static_cast<double>(height), 0, 0}}),
      xDistribution(0, width), yDistribution(0, height) {}

const std::vector<QLineF> &Map::getObstacles() const { return obstacles; }

void Map::addObstacle(const QPointF &startPoint, const QPointF &endPoint) {
    auto clipedLine = clipLineToFitMap({startPoint, endPoint});
    if (!clipedLine.isNull())
        obstacles.push_back(clipedLine);
}

void Map::removeObstacle(const QPointF &startPoint, const QPointF &endPoint) {
    QRectF removingRect(startPoint, endPoint);
    auto end = std::remove_if(obstacles.begin() + 4, obstacles.end(), [&](const auto &object) {
        return removingRect.contains(object.p1()) && removingRect.contains(object.p2());
    });

    obstacles.erase(end, obstacles.end());
}

QLineF Map::clipLineToFitMap(QLineF line) const {
    if (line.p1().x() > width) {
        QPointF intersectPoint;
        if (line.intersects(obstacles[1], &intersectPoint) == QLineF::NoIntersection)
            return {};
        line.setP1({static_cast<double>(width), intersectPoint.y()});

    } else if (line.p1().x() < 0) {
        QPointF intersectPoint;
        if (line.intersects(obstacles[3], &intersectPoint) == QLineF::NoIntersection)
            return {};
        line.setP1({0.0, intersectPoint.y()});
    }
    if (line.p1().y() > height) {
        QPointF intersectPoint;
        if (line.intersects(obstacles[2], &intersectPoint) == QLineF::NoIntersection)
            return {};
        line.setP1({intersectPoint.x(), static_cast<double>(height)});

    } else if (line.p1().y() < 0) {
        QPointF intersectPoint;
        if (line.intersects(obstacles[0], &intersectPoint) == QLineF::NoIntersection)
            return {};
        line.setP1({intersectPoint.x(), 0.0});
    }

    if (line.p2().x() > width) {
        QPointF intersectPoint;
        if (line.intersects(obstacles[1], &intersectPoint) == QLineF::NoIntersection)
            return {};
        line.setP2({static_cast<double>(width), intersectPoint.y()});

    } else if (line.p2().x() < 0) {
        QPointF intersectPoint;
        if (line.intersects(obstacles[3], &intersectPoint) == QLineF::NoIntersection)
            return {};
        line.setP2({0.0, intersectPoint.y()});
    }
    if (line.p2().y() > height) {
        QPointF intersectPoint;
        if (line.intersects(obstacles[2], &intersectPoint) == QLineF::NoIntersection)
            return {};
        line.setP2({intersectPoint.x(), static_cast<double>(height)});

    } else if (line.p2().y() < 0) {
        QPointF intersectPoint;
        if (line.intersects(obstacles[0], &intersectPoint) == QLineF::NoIntersection)
            return {};
        line.setP2({intersectPoint.x(), 0.0});
    }

    if (line.p1() == line.p2())
        return {};

    return line;
}
