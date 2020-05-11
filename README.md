# Pandemic-simulator

## Description
Program Pandemic-simulator provides visualization of a simple model of the virus(e.g. COVID-19) spreading during a pandemic. The model can be customized by different parameters such as spread distance, spread chance, mortality, recovering time, population size, and area size, also some parts of the population can be to lock down or separate from other parts. Model is a big simplification of reality and can not be used for any prediction. Anyway, a simplified model can be useful to visualize differences in virus spreading under different circumstances.

## Project page
https://panmareksadowski.github.io/Pandemic-simulator

## Demo
[<img src="https://cdn.loom.com/sessions/thumbnails/a188d653b17d4dbe898cd9747da72a1c-with-play.gif" alt="Demo 1" title="Demo 1" width="49%">](https://www.loom.com/share/a188d653b17d4dbe898cd9747da72a1c) [<img src="https://cdn.loom.com/sessions/thumbnails/845028336b8148c3b592ad8e4d5763b0-with-play.gif" alt="Demo 2" title="Demo 2" width="49%">](https://www.loom.com/share/845028336b8148c3b592ad8e4d5763b0)
[<img src="https://cdn.loom.com/sessions/thumbnails/cfc29412bc3f48318f90fd1ec6bead91-with-play.gif" alt="Demo 3" title="Demo 3" width="49%">](https://www.loom.com/share/cfc29412bc3f48318f90fd1ec6bead91)

## Download
Latest realease:  
[Win64bit installer](https://github.com/panmareksadowski/Pandemic-simulator/releases/latest/download/PandemicSimulatorWin64Setup.exe)  
[Win32bit installer](https://github.com/panmareksadowski/Pandemic-simulator/releases/latest/download/PandemicSimulatorWin32Setup.exe)  
[Source code and all assets](https://github.com/panmareksadowski/Pandemic-simulator/releases/latest)  

All releases: [link](https://github.com/panmareksadowski/Pandemic-simulator/releases)

## Build
### Build dependencies
- **qmake** is used as a build system
- **gcc** >= 7 or any other compiler that support c++17, has been tested with g++ 8.4.0 on ubuntu and g++ 7.3.0 from MinGw project on Windows
- **Qt** >= 5.14.0 has been tested with Qt 15.4.1

### Build instruction
On Linux:
```
mkdir build
cd build
qmake ../Pandemic-simulator.pro
make
```
On any system can be used Qt Creator Ide to build project with one click.(Please choose toolset >= 5.14)

## Notice
The program is consuming most of the available CPU to model calculations.

## License
Source code and the program are provided under GNU GENERAL PUBLIC LICENSE Version 3. Full license is available [here](https://github.com/panmareksadowski/Pandemic-simulator/blob/master/COPYING) and [here](https://github.com/panmareksadowski/Pandemic-simulator/blob/master/LICENSE).

Program used QT library under GPLv3 license. Here is [link](https://code.qt.io/cgit/) to source code.
