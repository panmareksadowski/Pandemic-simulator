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

#include <QSettings>

class ApplicationSettings : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool skipExpandOptionsHint READ getSkipExpandOptionsHint WRITE
                   setSkipExpandOptionsHint NOTIFY changedSkipExpandOptionsHint)

  signals:
    void changedSkipExpandOptionsHint();

  private:
    bool getSkipExpandOptionsHint() const {
        QSettings settings;
        return settings.value("hints/skip_expand_options_hint", false).toBool();
    }

    void setSkipExpandOptionsHint(bool skip) {
        QSettings settings;
        settings.setValue("hints/skip_expand_options_hint", skip);
        emit changedSkipExpandOptionsHint();
    }
};
