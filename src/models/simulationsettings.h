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
#include <chrono>

class SimulationSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(int propagateDistance READ getPropagateDistance WRITE setPropagateDistance NOTIFY
                   changedPropagateDistance)
    Q_PROPERTY(double propagateChance READ getPropagateChancePercent WRITE setPropagateChancePercent
                   NOTIFY changedPropagateChancePercent)
    Q_PROPERTY(int deadChance READ getDeadChancePercent WRITE setDeadChancePercent NOTIFY
                   changedDeadChancePercent)
    Q_PROPERTY(int recoveringTimeInMinutes READ getRecoveringTimeInMinutes WRITE
                   setRecoveringTimeInMinutes NOTIFY changedRecoveringTime)
    Q_PROPERTY(int recoveringTimeInHours READ getRecoveringTimeInHours WRITE
                   setRecoveringTimeInHours NOTIFY changedRecoveringTime)
    Q_PROPERTY(int recoveringTimeInDays READ getRecoveringTimeInDays WRITE setRecoveringTimeInDays
                   NOTIFY changedRecoveringTime)
    Q_PROPERTY(int dotSize READ getDotSize WRITE setDotSize NOTIFY changeDotSize)
    Q_PROPERTY(
        int acceleration READ getAcceleretion WRITE setAcceleretion NOTIFY changedAcceleretion)
  public:
    enum Unit { METERS, PIXELS };

    SimulationSettings(double metersPerPixel = 1, double propageteDistanceInM = 8,
                       double propagateChance = 1.0, double speedMPerS = 1.1111,
                       int acceleretion = 30, double deadChance = 0.05,
                       std::chrono::nanoseconds recoveringTime = std::chrono::minutes(30));

  public slots:
    void enlargeMap();
    void decreaseMap();

  public:
    double getMetersPerPixel() const;
    double getPixelPerMeter() const;

    void setPropagateDistance(double propagateDistance, Unit unit = METERS);
    double getPropagateDistance(Unit unit = METERS) const;

    void setPropagateChancePercent(double deadChancePercent);
    double getPropagateChancePercent() const;
    double getPropagateChance() const;

    double getSpeedPerS(Unit unit) const;

    double getDistancePerElapsedTime(const std::chrono::nanoseconds &elapsedTime, Unit unit) const;

    int getAcceleretion() const;
    void setAcceleretion(int acceleretion);
    void forceDecreaseAcceleretion(double percent);

    void setDeadChancePercent(int deadChancePercent);
    int getDeadChancePercent() const;
    double getDeadChance() const;

    void setRecoveringTimeInMinutes(int recoveringTimeInMinutes);
    std::chrono::minutes::rep getRecoveringTimeInMinutes() const;
    void setRecoveringTimeInHours(int recoveringTimeInHours);
    std::chrono::hours::rep getRecoveringTimeInHours() const;
    void setRecoveringTimeInDays(int recoveringTimeInDays);
    std::chrono::hours::rep getRecoveringTimeInDays() const;
    std::chrono::nanoseconds getRecoveringTime() const;

    void setDotSize(int dotSize);
    int getDotSize() const;
  signals:
    void changedPropagateDistance();
    void changedPropagateChancePercent();
    void changedDeadChancePercent();
    void changedRecoveringTime();
    void changeDotSize();
    void changedAcceleretion();
    void accelleretionDecresed();

  private:
    double metersPerPixel;
    double propageteDistanceInM;
    double propagateChance;
    const double speedMPerS;
    int acceleretion;
    double deadChance;
    std::chrono::nanoseconds recoveringTime;

    int dotSize = 2;
};
