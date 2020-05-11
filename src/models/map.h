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
#include <random>
#include <vector>

class Map {
  public:
    Map(int width = 1920, int height = 1080);

  public:
    const std::vector<QLineF> &getObstacles() const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    std::uniform_real_distribution<double> getXDistribution() const { return xDistribution; }
    std::uniform_real_distribution<double> getYDistribution() const { return yDistribution; }

    void addObstacle(const QPointF &startPoint, const QPointF &endPoint);
    void removeObstacle(const QPointF &startPoint, const QPointF &endPoint);

  private:
    QLineF clipLineToFitMap(QLineF line) const;
    const int width;
    const int height;

    std::vector<QLineF> obstacles; // TODO: use alias for obstacle type

    std::uniform_real_distribution<double> xDistribution;
    std::uniform_real_distribution<double> yDistribution;
};
