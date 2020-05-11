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

#include "personstatus.h"

#include "utils/randomgeneretor.hpp"

using namespace std::chrono_literals;
using std::chrono::nanoseconds;

PersonStatus PersonStatus::createHealthStatus() { return PersonStatus{}; }

PersonStatus PersonStatus::createIllStatus(double deadChance,
                                           const nanoseconds &averageRecoveringTime) {
    PersonStatus newStatus;
    newStatus.markIll(deadChance, 0ns, averageRecoveringTime);
    return newStatus;
}

void PersonStatus::updateRecoverStatus(const nanoseconds &time) {
    if (time > recoverTime)
        markRecover();
}

void PersonStatus::meetWithIllPerson(double deadChance, double propagateChance,
                                     const nanoseconds &time, const nanoseconds &recoveringTime) {
    if (time - lastMeetingTime > minTimeBetweenMeetings) {
        lastMeetingTime = time;
        // TODO: random generetion is relatively computational cost expensive, refactor it to use
        // random generetor less often
        if (normalDistribution(getRandomGeneretor()) < propagateChance)
            markIll(deadChance, time, recoveringTime);
    }
}

bool PersonStatus::isDead(const nanoseconds &time) const { return time > deadTime; }

void PersonStatus::markRecover() { status = RECOVERED; }

void PersonStatus::markIll(double deadChance, const nanoseconds &time,
                           const nanoseconds &averageRecoveringTime) {
    if (status != ILL) {
        status = ILL;
        appointDeadOrRecoverTime(deadChance, time, averageRecoveringTime);
    }
}

void PersonStatus::appointDeadOrRecoverTime(double deadChance, const nanoseconds &time,
                                            const nanoseconds &averageRecoveringTime) {
    if (normalDistribution(getRandomGeneretor()) < deadChance)
        appointDeadTime(time, averageRecoveringTime);
    else
        appointRecoverTime(time, averageRecoveringTime);
}

void PersonStatus::appointRecoverTime(const nanoseconds &time,
                                      const nanoseconds &averageRecoveringTime) {
    std::normal_distribution<> timeToRecoverGeneretor(averageRecoveringTime.count(),
                                                      averageRecoveringTime.count() / 10);
    recoverTime =
        time +
        nanoseconds(static_cast<nanoseconds::rep>(timeToRecoverGeneretor(getRandomGeneretor())));
}

void PersonStatus::appointDeadTime(const nanoseconds &time,
                                   const nanoseconds &averageRecoveringTime) {
    std::normal_distribution<> timeToDeadGeneretor(0.9 * averageRecoveringTime.count(),
                                                   averageRecoveringTime.count() / 8);
    deadTime = time + nanoseconds(
                          static_cast<nanoseconds::rep>(timeToDeadGeneretor(getRandomGeneretor())));
}
