import QtQuick 2.14
import QtQuick.Controls 2.14

Dialog {
    modal: true

    Column {

        spacing: 12

        Label {
            text: "Built from <a href=\"https://github.com/panmareksadowski/Pandemic-simulator/releases/tag/v"
                  + Qt.application.version + "\">source code</a>"
            onLinkActivated: Qt.openUrlExternally(link)
        }

        Label {
            text: "Built with " + compilerversion
        }

        Label {
            text: "Based on Qt " + qtversion
        }

        Label {
            text: "Copyright 2020 Marek Sadowski

Pandemic-simulator is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

Pandemic-simulator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Pandemic-simulator.  If not, see <http://www.gnu.org/licenses/>."
        }
    }

    standardButtons: Dialog.Close
    title: Qt.application.name + " v" + Qt.application.version
}
