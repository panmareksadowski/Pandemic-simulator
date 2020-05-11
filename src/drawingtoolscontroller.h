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

#include "utils/enums.h"

class Map;

class DrawingToolsController : public QObject {
    Q_OBJECT
    Q_PROPERTY(Enums::DrawingTool leftClickSelectedTool READ getLeftCLickSelectedTool WRITE
                   setLeftCLickSelectedTool NOTIFY changedLeftClickSelectedTool)
  public:
    DrawingToolsController(Map &map);
  public slots:
    void leftClickAction(const QPointF &startPoint, const QPointF &endPoint);
    void rightClickAction(const QPointF &startPoint, const QPointF &endPoint);
  signals:
    void changedLeftClickSelectedTool();

  private:
    void toolAction(Enums::DrawingTool tool, const QPointF &startPoint, const QPointF &endPoint);

    Enums::DrawingTool getLeftCLickSelectedTool() const;
    void setLeftCLickSelectedTool(Enums::DrawingTool selectedTool);

    Map &map;
    Enums::DrawingTool leftClickSelectedTool = Enums::NOTOOL;
    const Enums::DrawingTool rightClickSelectedTool = Enums::RUBBERRECT;
};
