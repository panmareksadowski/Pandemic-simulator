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

#include "drawingtoolscontroller.h"

#include "models/map.h"

DrawingToolsController::DrawingToolsController(Map &map) : map(map) {}

void DrawingToolsController::leftClickAction(const QPointF &startPoint, const QPointF &endPoint) {
    toolAction(leftClickSelectedTool, startPoint, endPoint);
}

void DrawingToolsController::rightClickAction(const QPointF &startPoint, const QPointF &endPoint) {
    toolAction(rightClickSelectedTool, startPoint, endPoint);
}

void DrawingToolsController::toolAction(Enums::DrawingTool tool, const QPointF &startPoint,
                                        const QPointF &endPoint) {
    switch (tool) {
    case Enums::LINE:
        map.addObstacle(startPoint, endPoint);
        break;
    case Enums::RECT:
        map.addObstacle(startPoint, {endPoint.x(), startPoint.y()});
        map.addObstacle({endPoint.x(), startPoint.y()}, endPoint);
        map.addObstacle(endPoint, {startPoint.x(), endPoint.y()});
        map.addObstacle({startPoint.x(), endPoint.y()}, startPoint);
        break;
    case Enums::RUBBERRECT:
        map.removeObstacle(startPoint, endPoint);
        break;
    default:
        break;
    }
}

Enums::DrawingTool DrawingToolsController::getLeftCLickSelectedTool() const {
    return leftClickSelectedTool;
}

void DrawingToolsController::setLeftCLickSelectedTool(Enums::DrawingTool selectedTool) {
    leftClickSelectedTool = selectedTool;
    changedLeftClickSelectedTool();
}
