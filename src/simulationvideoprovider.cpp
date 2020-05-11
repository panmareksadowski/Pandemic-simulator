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

#include "simulationvideoprovider.h"

#include "models/map.h"

SimulationVideoProvider::SimulationVideoProvider(const Map &map)
    : format({map.getWidth(), map.getHeight()}, QVideoFrame::Format_RGB32) {}

void SimulationVideoProvider::setVideoSurface(QAbstractVideoSurface *newSurface) {
    if (surface != newSurface && surface && surface->isActive()) {
        surface->stop();
    }
    surface = newSurface;
    if (surface) {
        QImage image(format.frameSize(), QImage::Format_RGB32);
        image.fill(QColor("white"));
        surface->present(image);
        surface->start(format);
    }
}

void SimulationVideoProvider::setNewFrame(const QVideoFrame &frame) {
    if (surface) {
        surface->present(frame);
    }
}
