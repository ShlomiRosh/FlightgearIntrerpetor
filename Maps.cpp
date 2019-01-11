#include "Maps.h"
map<string, string> Maps::mapOfPath;
map<string, double> Maps::pathsValues;
map<string, double> Maps::symbolTable;

map<string, string> Maps::getMapOfPath() {
    return mapOfPath;
}

void Maps::setMapOfPath(string kay, string path) {
    mapOfPath.insert(pair<string, string>(kay, path));
}

map<string, double> &Maps::getPathsValues() {
    return pathsValues;
}

void Maps::setPathsValues(string kayPath, double value) {
    if (!pathsValues.count(kayPath) || pathsValues.find(kayPath)->second != value) {
        if (!pathsValues.count(kayPath)) {
            pathsValues.insert(pair<string, double>(kayPath, value));
        } else if (pathsValues.find(kayPath)->second != value) {
            pathsValues.find(kayPath)->second = value;
        }
    }
}

map<string, double> &Maps::getSymbolTable() {
    return symbolTable;
}

void Maps::setSymbolTable(string kayVar, double value) {
    if (!symbolTable.count(kayVar) || symbolTable.find(kayVar)->second != value) {
        if (!symbolTable.count(kayVar)) {
            symbolTable.insert(pair<string, double>(kayVar, value));
        } else if (symbolTable.find(kayVar)->second != value) {
            symbolTable.find(kayVar)->second = value;
        }
    }
}

void Maps::initMapPathsValue() {
    setPathsValues("/instrumentation/airspeed-indicator/indicated-speed-kt", 0);
    setPathsValues("/instrumentation/altimeter/indicated-altitude-ft", 0);
    setPathsValues("/instrumentation/altimeter/pressure-alt-ft", 0);
    setPathsValues("/instrumentation/attitude-indicator/indicated-pitch-deg", 0);
    setPathsValues("/instrumentation/attitude-indicator/indicated-roll-deg", 0);
    setPathsValues("/instrumentation/attitude-indicator/internal-pitch-deg", 0);
    setPathsValues("/instrumentation/attitude-indicator/internal-roll-deg", 0);
    setPathsValues("/instrumentation/encoder/indicated-altitude-ft", 0);
    setPathsValues("/instrumentation/encoder/pressure-alt-ft", 0);
    setPathsValues("/instrumentation/gps/indicated-altitude-ft", 0);
    setPathsValues("/instrumentation/gps/indicated-ground-speed-kt", 0);
    setPathsValues("/instrumentation/gps/indicated-vertical-speed", 0);
    setPathsValues("/instrumentation/heading-indicator/indicated-heading-deg", 0);
    setPathsValues("/instrumentation/magnetic-compass/indicated-heading-deg", 0);
    setPathsValues("/instrumentation/slip-skid-ball/indicated-slip-skid", 0);
    setPathsValues("/instrumentation/turn-indicator/indicated-turn-rate", 0);
    setPathsValues("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0);
    setPathsValues("/controls/flight/aileron", 0);
    setPathsValues("/controls/flight/elevator", 0);
    setPathsValues("/controls/flight/rudder", 0);
    setPathsValues("/controls/flight/flaps", 0);
    setPathsValues("/controls/engines/current-engine/throttle", 0);
    setPathsValues("/engines/engine/rpm", 0);
}
