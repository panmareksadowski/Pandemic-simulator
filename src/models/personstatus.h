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

#include <chrono>
#include <random>

class PersonStatus {
  public:
    enum Status { HEALTH, ILL, RECOVERED };
    static PersonStatus createHealthStatus();
    static PersonStatus createIllStatus(double deadChance,
                                        const std::chrono::nanoseconds &averageRecoveringTime);

    void updateRecoverStatus(const std::chrono::nanoseconds &averageRecoveringTime);

    void meetWithIllPerson(double deadChance, double propagateChance,
                           const std::chrono::nanoseconds &meetingTime,
                           const std::chrono::nanoseconds &averageRecoveringTime);

    Status getStatus() const { return status; }

    bool isDead(const std::chrono::nanoseconds &duration) const;

  private:
    PersonStatus() = default;

    void markRecover();

    void markIll(double deadChance, const std::chrono::nanoseconds &time,
                 const std::chrono::nanoseconds &averageRecoveringTime);

    void appointDeadOrRecoverTime(double deadChance, const std::chrono::nanoseconds &time,
                                  const std::chrono::nanoseconds &averageRecoveringTime);

    void appointRecoverTime(const std::chrono::nanoseconds &time,
                            const std::chrono::nanoseconds &averageRecoveringTime);

    void appointDeadTime(const std::chrono::nanoseconds &time,
                         const std::chrono::nanoseconds &averageRecoveringTime);

    Status status = HEALTH;
    static constexpr std::chrono::nanoseconds minTimeBetweenMeetings = std::chrono::seconds(2);
    std::chrono::nanoseconds lastMeetingTime = std::chrono::seconds(-1);
    std::chrono::nanoseconds recoverTime = std::chrono::nanoseconds::max();
    std::chrono::nanoseconds deadTime = std::chrono::nanoseconds::max();

    static inline std::uniform_real_distribution<double> normalDistribution{0, 1};
};
