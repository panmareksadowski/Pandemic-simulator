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

#include <QPainter>

class Map;
class Person;
class PersonsList;
class SimulationSettings;
class SimulationVideoProvider;

class SimulationDrawer {
  public:
    SimulationDrawer(SimulationVideoProvider &videoSource);

    void draw(const Map &map, const PersonsList &personsList, const SimulationSettings &settings);

  private:
    SimulationVideoProvider &videoSource;

    void drawMap(QPainter &painter, const Map &map);
    void drawPersons(QPainter &painter, const PersonsList &personsList,
                     const SimulationSettings &settings);
    void drawPerson(QPainter &painter, const Person &person, const SimulationSettings &settings);
    void drawScale(QPainter &painter, const SimulationSettings &settings, int imageHeight);
};
