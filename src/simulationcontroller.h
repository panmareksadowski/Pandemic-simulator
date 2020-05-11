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

#include <QObject>
#include <QTimer>

#include "utils/enums.h"

class Map;
class SimulationSettings;
class SimulationExecutor;
class SimulationDrawer;
class SimulationStatistics;

class SimulationController : public QObject {
    Q_OBJECT
    Q_PROPERTY(Enums::ControllerStatus status READ getStatus NOTIFY changedStatus)

  public:
    explicit SimulationController(const Map &map, const SimulationSettings &simulationSettings,
                                  SimulationExecutor &simulationExecutor,
                                  SimulationDrawer &simulationDrawer,
                                  SimulationStatistics &simulationStatisctics);

  public slots:
    void play(int numberOfPersons, int percentStoppedPersons);
    void pause();
    void stop();
  signals:
    void changedStatus();
  protected slots:
    void refresh();

  private:
    Enums::ControllerStatus getStatus();

    QTimer refreshTimer;
    Enums::ControllerStatus status = Enums::STOP;

    const Map &map;
    const SimulationSettings &simulationSettings;
    SimulationExecutor &simulationExecutor;
    SimulationDrawer &simulationDrawer;
    SimulationStatistics &simulationStatisctics;
};
