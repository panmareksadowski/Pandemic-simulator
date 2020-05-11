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

#include "periodicallyinvoker.h"

class PersonsList;

class DeadPersonsRemover : protected PeriodicallyInvoker {
  public:
    DeadPersonsRemover(PersonsList &personsList);

    void removeDeadPersons(const std::chrono::nanoseconds &time);

    using PeriodicallyInvoker::reset;

  protected:
    void action(const std::chrono::nanoseconds &time) override;

  private:
    PersonsList &personsList;
};
