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

#include "simulationdrawer.h"

#include "models/map.h"
#include "models/person.h"
#include "models/personslist.h"
#include "models/simulationsettings.h"
#include "simulationvideoprovider.h"
#include "utils/applicationcolors.hpp"

SimulationDrawer::SimulationDrawer(SimulationVideoProvider &videoSource)
    : videoSource(videoSource) {}

void SimulationDrawer::draw(const Map &map, const PersonsList &personsList,
                            const SimulationSettings &settings) {
    QImage image(videoSource.frameSize(), QImage::Format_RGB32);
    image.fill(Qt::white);

    {
        QPainter painter(&image);

        drawMap(painter, map);
        drawPersons(painter, personsList, settings);
        drawScale(painter, settings, image.height());
    }

    videoSource.setNewFrame(image);
}

void SimulationDrawer::drawMap(QPainter &painter, const Map &map) {
    painter.setPen(Qt::black);
    for (const auto &obstacle : map.getObstacles())
        painter.drawLine(obstacle);
}

void SimulationDrawer::drawPersons(QPainter &painter, const PersonsList &personsList,
                                   const SimulationSettings &settings) {
    for (const auto &person : personsList)
        drawPerson(painter, person, settings);
}

void SimulationDrawer::drawPerson(QPainter &painter, const Person &person,
                                  const SimulationSettings &settings) {
    switch (person.getStatus()) {
    case PersonStatus::HEALTH:
        painter.setPen(ApplicationColors::instance()->getHealthColor());
        painter.setBrush(ApplicationColors::instance()->getHealthColor());
        break;
    case PersonStatus::ILL:
        painter.setPen(ApplicationColors::instance()->getIllColor());
        painter.setBrush(ApplicationColors::instance()->getIllColor());
        break;
    case PersonStatus::RECOVERED:
        painter.setPen(ApplicationColors::instance()->getRecoveredColor());
        painter.setBrush(ApplicationColors::instance()->getRecoveredColor());
        break;
    }

    painter.drawEllipse(person.getCordinates(), settings.getDotSize(), settings.getDotSize());
    if (person.getStatus() == PersonStatus::ILL) {
        painter.setPen(ApplicationColors::instance()->getIllColor());
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(person.getCordinates(),
                            settings.getPropagateDistance(SimulationSettings::PIXELS),
                            settings.getPropagateDistance(SimulationSettings::PIXELS));
    }
}

void SimulationDrawer::drawScale(QPainter &painter, const SimulationSettings &settings,
                                 int imageHeight) {
    painter.setPen(Qt::black);
    painter.setBrush(Qt::NoBrush);
    if (settings.getMetersPerPixel() < 0.5) {
        painter.drawRect(15, imageHeight - 25, static_cast<int>(10 / settings.getMetersPerPixel()),
                         2);
        painter.drawText(15, imageHeight - 10, "10m");
    } else if (settings.getMetersPerPixel() < 5) {
        painter.drawRect(15, imageHeight - 25, static_cast<int>(100 / settings.getMetersPerPixel()),
                         2);
        painter.drawText(15, imageHeight - 10, "100m");
    } else {
        painter.drawRect(15, imageHeight - 25,
                         static_cast<int>(1000 / settings.getMetersPerPixel()), 2);
        painter.drawText(15, imageHeight - 10, "1km");
    }
}
