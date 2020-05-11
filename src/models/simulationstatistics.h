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

#include "models/personslist.h"

class SimulationStatistics : public QObject {
    Q_OBJECT

    Q_PROPERTY(int allPersons READ getAllPersons NOTIFY dataUpdated)
    Q_PROPERTY(int alive READ getAlive NOTIFY dataUpdated)
    Q_PROPERTY(int health READ getHealth NOTIFY dataUpdated)
    Q_PROPERTY(int ill READ getIll NOTIFY dataUpdated)
    Q_PROPERTY(int recovered READ getRecovered NOTIFY dataUpdated)
    Q_PROPERTY(int dead READ getDead NOTIFY dataUpdated)
    Q_PROPERTY(int infected READ getInfected NOTIFY dataUpdated)
    Q_PROPERTY(int durationMinutes READ getDurationInMinutes NOTIFY dataUpdated)
  public:
    void updateData(const PersonsList &personsList, const std::chrono::nanoseconds &duration);
    void resetData(int allPersons = 0);
    int getAllPersons() const;
    int getAlive() const;
    int getIll() const;
    int getHealth() const;
    int getRecovered() const;
    int getDead() const;
    int getInfected() const;
    std::chrono::minutes::rep getDurationInMinutes() const;

  signals:
    void dataUpdated();

  private:
    void recalculateStatistics(const PersonsList &personsList);

    int allPersons = 0;
    int alivePersons = 0;
    int healthPersons = 0;
    int deadPersons = 0;
    int illPersons = 0;
    int recoveredPersons = 0;
    std::chrono::nanoseconds duration = std::chrono::nanoseconds(0);
};
