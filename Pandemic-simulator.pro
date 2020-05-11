#Copyright 2020 Marek Sadowski

#This file is part of Pandemic-simulator.
#Pandemic-simulator is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 3 of the License, or
#(at your option) any later version.

#Pandemic-simulator is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.

#You should have received a copy of the GNU General Public License
#along with Pandemic-simulator.  If not, see <http://www.gnu.org/licenses/>.

!versionAtLeast(QT_VERSION, 5.14.0):error("The minimum Qt required version is 5.14.0.")

VERSION = 1.0.0
DEFINES += APPLICATION_VERSION='\\"$${VERSION}\\"'

#if c++ compiler has --version command line options
system("$$QMAKE_CXX --version"){
    #get --version output
    COMPILER_VERSION = $$system("$$QMAKE_CXX --version", lines)
    #get only first line if --version produce multiline output
    #for g++ first line has all important info
    COMPILER_VERSION = $$first(COMPILER_VERSION)
    DEFINES += COMPILER_VERSION='\\"$$shell_quote($$COMPILER_VERSION)\\"'
} else {
    #if compiler has no --version command line options just get compiler name
    DEFINES += COMPILER_VERSION='\\"$$QMAKE_CXX\\"'
}

QT += multimedia quickcontrols2 charts concurrent
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        src/application.cpp \
        src/deadpersonsremover.cpp \
        src/drawingtoolscontroller.cpp \
        src/main.cpp \
        src/models/map.cpp \
        src/models/person.cpp \
        src/models/personposition.cpp \
        src/models/personslist.cpp \
        src/models/personstatus.cpp \
        src/models/simulationsettings.cpp \
        src/models/simulationstatistics.cpp \
        src/periodicallyinvoker.cpp \
        src/personsmovecontroller.cpp \
        src/recoveredpersonsmarker.cpp \
        src/simulationcontroller.cpp \
        src/simulationdrawer.cpp \
        src/simulationexecutor.cpp \
        src/simulationvideoprovider.cpp

RESOURCES += \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += src/

HEADERS += \
    src/application.h \
    src/deadpersonsremover.h \
    src/drawingtoolscontroller.h \
    src/models/applicationsettings.hpp \
    src/models/map.h \
    src/models/person.h \
    src/models/personposition.h \
    src/models/personslist.h \
    src/models/personstatus.h \
    src/models/simulation.hpp \
    src/models/simulationsettings.h \
    src/models/simulationstatistics.h \
    src/periodicallyinvoker.h \
    src/personsmovecontroller.h \
    src/recoveredpersonsmarker.h \
    src/simulationcontroller.h \
    src/simulationdrawer.h \
    src/simulationexecutor.h \
    src/simulationvideoprovider.h \
    src/utils/applicationcolors.hpp \
    src/utils/enums.h \
    src/utils/geometry.hpp \
    src/utils/randomgeneretor.hpp

win32: RC_ICONS = icon.ico
