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

#include <QThread>

#include "deadpersonsremover.h"
#include "models/personslist.h"
#include "personsmovecontroller.h"
#include "recoveredpersonsmarker.h"
#include "utils/enums.h"

class Map;
class SimulationSettings;

class SimulationExecutor : public QThread {
  public:
    SimulationExecutor(const Map &map, SimulationSettings &settings);
    ~SimulationExecutor() override;

    void play(int numberOfRunPersons, int numberOfStoppedPersons);
    void pause();
    void stop();

    PersonsList getPersonsList() const;
    std::chrono::nanoseconds getDuration() const;

  private:
    void clearPersons();
    void addPersons(int numberOfRunPersons, int numberOfStoppedPersons);
    void resetDuration();

    void run() override;

    void tick(const std::chrono::nanoseconds &elapsedFromLastTick);

    void markLastTick();
    std::chrono::nanoseconds getElapsedTimeFromLastTickAndMarkLastTick();

    bool finishThread = false;

    PersonsList personsList;

    std::chrono::nanoseconds duration = std::chrono::nanoseconds(0);
    std::chrono::time_point<std::chrono::steady_clock> lastTickTime;

    const Map &map;
    SimulationSettings &settings;
    Enums::ControllerStatus status = Enums::STOP;

    RecoveredPersonsMarker recoveredPersonsMarker; // TODO: use pimpl
    DeadPersonsRemover deadPersonsRemover;
    PersonsMoveController personsMoveController;
};
