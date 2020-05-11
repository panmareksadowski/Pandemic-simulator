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
#include <QtMath>

// TODO: use alias for parameters(Movment instead of QLineF), rename function
// function return nearest distance between points that are moving from QLineF.p1() to QLineF.p2()
// with assumption that both points are overcoming their distance in same time(for example if line1
// is 2 times loner that line2 means that point 1 is moving 2 times faster that point 2)
double nearestDistance(QLineF line1, QLineF line2) {
    double coefficient1 =
        line2.length() > 0 ? (line1.length() / line2.length()) : (line1.length() > 0 ? 1.0 : 0.0);
    double coefficient2 = line2.length() > 0 ? 1.0 : 0.0;

    double dx = line1.p1().x() - line2.p1().x();
    double dcos = coefficient1 * qCos(qDegreesToRadians(360 - line1.angle())) -
                  coefficient2 * qCos(qDegreesToRadians(360 - line2.angle()));
    double dy = line1.p1().y() - line2.p1().y();
    double dsin = coefficient1 * qSin(qDegreesToRadians(360 - line1.angle())) -
                  coefficient2 * qSin(qDegreesToRadians(360 - line2.angle()));

    double denominator = -dcos * dx - dsin * dy;
    double devider = dcos * dcos + dsin * dsin;
    double xmin = 0.0;
    if (devider != 0.0)
        xmin = denominator / devider;
    double xmin1 = coefficient1 * xmin;
    xmin1 = std::max(xmin1, 0.0);
    xmin1 = std::min(xmin1, line1.length());
    double xmin2 = coefficient2 * xmin;
    xmin2 = std::max(xmin2, 0.0);
    xmin2 = std::min(xmin2, line2.length());

    line1.setLength(xmin1);
    line2.setLength(xmin2);
    return QLineF(line1.p2(), line2.p2()).length();
}
