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

#include "application.h"

#include <QQmlContext>
#include <QQuickStyle>

#include "utils/applicationcolors.hpp"
#include "utils/enums.h"

Application::Application(int &argc, char **argv) : QApplication(argc, argv) {
    setApplicationName("Pandemic-simulator");
    setOrganizationName("Pandemic-simulator");
    setOrganizationDomain("panmareksadowski.github.io");
    setApplicationVersion(APPLICATION_VERSION);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&qmlEngine, &QQmlApplicationEngine::objectCreated, this,
                     [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     },
                     Qt::QueuedConnection);

    qmlRegisterType<Enums>("Enums", 1, 0, "Enums");
    qRegisterMetaType<Enums::ControllerStatus>("Enums::ControllerStatus");
    qRegisterMetaType<Enums::DrawingTool>("Enums::DrawingTool");

    qmlEngine.rootContext()->setContextProperty("qtversion", QString(qVersion()));
    qmlEngine.rootContext()->setContextProperty("compilerversion", QString(COMPILER_VERSION));
    qmlEngine.rootContext()->setContextProperty("Controller", simulation.getSimulationController());
    qmlEngine.rootContext()->setContextProperty("Statistics", simulation.getSimulationStatistics());
    qmlEngine.rootContext()->setContextProperty("SimulationSettings",
                                                simulation.getSimulationSettings());
    qmlEngine.rootContext()->setContextProperty("DrawingToolsController",
                                                simulation.getDrawingToolsController());
    qmlEngine.rootContext()->setContextProperty("VideoSource",
                                                simulation.getSimulationVideoProvider());
    qmlEngine.rootContext()->setContextProperty("AppSettings", &settings);
    qmlEngine.rootContext()->setContextProperty("AppColors", ApplicationColors::instance());
    qmlEngine.load(url);
}
