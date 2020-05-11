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

#include "simulationsettings.h"

SimulationSettings::SimulationSettings(double metersPerPixel, double propageteDistanceInM,
                                       double propagateChance, double speedMPerS, int acceleretion,
                                       double deadChance, std::chrono::nanoseconds recoveringTime)
    : metersPerPixel(metersPerPixel), propageteDistanceInM(propageteDistanceInM),
      propagateChance(propagateChance), speedMPerS(speedMPerS), acceleretion(acceleretion),
      deadChance(deadChance), recoveringTime(recoveringTime) {}

void SimulationSettings::enlargeMap() {
    if (metersPerPixel > 0.1)
        metersPerPixel /= 2.0;
}

void SimulationSettings::decreaseMap() {
    if (metersPerPixel < 100)
        metersPerPixel *= 2.0;
}

double SimulationSettings::getMetersPerPixel() const { return metersPerPixel; }

double SimulationSettings::getPixelPerMeter() const { return 1.0 / metersPerPixel; }

void SimulationSettings::setPropagateDistance(double propagateDistance, Unit unit) {
    switch (unit) {
    case METERS:
        propageteDistanceInM = propagateDistance;
        break;
    case PIXELS:
        propageteDistanceInM = propagateDistance * metersPerPixel;
    }
    emit changedPropagateDistance();
}

double SimulationSettings::getPropagateDistance(Unit unit) const {
    switch (unit) {
    case METERS:
        return propageteDistanceInM;
    case PIXELS:
        return propageteDistanceInM / metersPerPixel;
    }
    return 0;
}

void SimulationSettings::setPropagateChancePercent(double propagateChancePercent) {
    propagateChance = propagateChancePercent / 100.0;
    emit changedPropagateChancePercent();
}

double SimulationSettings::getPropagateChancePercent() const { return propagateChance * 100.0; }

double SimulationSettings::getPropagateChance() const { return propagateChance; }

double SimulationSettings::getSpeedPerS(Unit unit) const {
    switch (unit) {
    case METERS:
        return speedMPerS;
    case PIXELS:
        return speedMPerS / metersPerPixel;
    }
    return 0;
}

double SimulationSettings::getDistancePerElapsedTime(const std::chrono::nanoseconds &elapsedTime,
                                                     Unit unit) const {
    return getAcceleretion() * getSpeedPerS(unit) * elapsedTime.count() * 10e-9;
}

int SimulationSettings::getAcceleretion() const { return acceleretion; }

void SimulationSettings::setAcceleretion(int acceleretion) {
    this->acceleretion = acceleretion;
    emit changedAcceleretion();
}

void SimulationSettings::forceDecreaseAcceleretion(double percent) {
    setAcceleretion(static_cast<int>(acceleretion * percent));
    emit accelleretionDecresed();
}

void SimulationSettings::setDeadChancePercent(int deadChancePercent) {
    deadChance = deadChancePercent / 100.0;
    emit changedDeadChancePercent();
}

int SimulationSettings::getDeadChancePercent() const { return static_cast<int>(deadChance * 100); }

double SimulationSettings::getDeadChance() const { return deadChance; }

void SimulationSettings::setRecoveringTimeInMinutes(int recoveringTimeInMinutes) {
    recoveringTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::minutes(recoveringTimeInMinutes));
    emit changedRecoveringTime();
}

std::chrono::minutes::rep SimulationSettings::getRecoveringTimeInMinutes() const {
    return std::chrono::duration_cast<std::chrono::minutes>(recoveringTime).count();
}

void SimulationSettings::setRecoveringTimeInHours(int recoveringTimeInHours) {
    recoveringTime = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::hours(recoveringTimeInHours));
    emit changedRecoveringTime();
}

std::chrono::hours::rep SimulationSettings::getRecoveringTimeInHours() const {
    return std::chrono::duration_cast<std::chrono::hours>(recoveringTime).count();
}

void SimulationSettings::setRecoveringTimeInDays(int recoveringTimeInDays) {
    setRecoveringTimeInHours(24 * recoveringTimeInDays);
}

std::chrono::hours::rep SimulationSettings::getRecoveringTimeInDays() const {
    return getRecoveringTimeInHours() / 24;
}

std::chrono::nanoseconds SimulationSettings::getRecoveringTime() const { return recoveringTime; }

void SimulationSettings::setDotSize(int dotSize) {
    this->dotSize = dotSize;
    emit changeDotSize();
}

int SimulationSettings::getDotSize() const { return dotSize; }
