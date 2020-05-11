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

#include <QColor>
#include <QObject>

class ApplicationColors : public QObject {
    Q_OBJECT

    Q_PROPERTY(QColor dirtyWhiteColor READ getDirtyWhiteColor CONSTANT)
    Q_PROPERTY(QColor healthColor READ getHealthColor CONSTANT)
    Q_PROPERTY(QColor aliveColor READ getAliveColor CONSTANT)
    Q_PROPERTY(QColor recoveredColor READ getRecoveredColor CONSTANT)
    Q_PROPERTY(QColor illColor READ getIllColor CONSTANT)
    Q_PROPERTY(QColor deadColor READ getDeadColor CONSTANT)
    Q_PROPERTY(QColor infectedColor READ getInfectedColor CONSTANT)
    Q_PROPERTY(QColor warningColor READ getWarningColor CONSTANT)
  public:
    static ApplicationColors *instance() {
        static ApplicationColors applicationColors;
        return &applicationColors;
    }

    QColor getDirtyWhiteColor() const { return "#cccccc"; }
    QColor getHealthColor() const { return "#00b300"; }
    QColor getAliveColor() const { return getHealthColor(); }
    QColor getRecoveredColor() const { return "#0077b3"; }
    QColor getIllColor() const { return "#b30000"; }
    QColor getDeadColor() const { return "#800000"; }
    QColor getInfectedColor() const { return getIllColor(); }
    QColor getWarningColor() const { return "red"; }

  private:
    ApplicationColors() {}
};
