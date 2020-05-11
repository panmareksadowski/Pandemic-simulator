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

#include "drawingtoolscontroller.h"
#include "models/map.h"
#include "models/simulationsettings.h"
#include "models/simulationstatistics.h"
#include "simulationcontroller.h"
#include "simulationdrawer.h"
#include "simulationexecutor.h"
#include "simulationvideoprovider.h"

class Simulation {
  public:
    Simulation()
        : simulationExecutor(map, simulationSettings), drawingToolsController(map),
          simulationVideoProvider(map), simulationDrawer(simulationVideoProvider),
          simulationController(map, simulationSettings, simulationExecutor, simulationDrawer,
                               simulationStatisctics) {}

    SimulationVideoProvider *getSimulationVideoProvider() { return &simulationVideoProvider; }
    DrawingToolsController *getDrawingToolsController() { return &drawingToolsController; }
    SimulationSettings *getSimulationSettings() { return &simulationSettings; }
    SimulationStatistics *getSimulationStatistics() { return &simulationStatisctics; }
    SimulationController *getSimulationController() { return &simulationController; }

  private:
    Map map;
    SimulationSettings simulationSettings;
    SimulationExecutor simulationExecutor;
    DrawingToolsController drawingToolsController;
    SimulationVideoProvider simulationVideoProvider;
    SimulationDrawer simulationDrawer;
    SimulationStatistics simulationStatisctics;
    SimulationController simulationController;
};
