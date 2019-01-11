#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "Maps.h"
#include <sstream>
class ReadBufferServer {

public:

    static void updatMaps(string buffer) {
        vector<string> values = getValues(buffer, ','); // Split the string.
        Maps::setPathsValues("/instrumentation/airspeed-indicator/indicated-speed-kt", stod(values.at(0)));
        Maps::setPathsValues("/instrumentation/altimeter/indicated-altitude-ft", stod(values.at(1)));
        Maps::setPathsValues("/instrumentation/altimeter/pressure-alt-ft", stod(values.at(2)));
        Maps::setPathsValues("/instrumentation/attitude-indicator/indicated-pitch-deg", stod(values.at(3)));
        Maps::setPathsValues("/instrumentation/attitude-indicator/indicated-roll-deg", stod(values.at(4)));
        Maps::setPathsValues("/instrumentation/attitude-indicator/internal-pitch-deg", stod(values.at(5)));
        Maps::setPathsValues("/instrumentation/attitude-indicator/internal-roll-deg", stod(values.at(6)));
        Maps::setPathsValues("/instrumentation/encoder/indicated-altitude-ft", stod(values.at(7)));
        Maps::setPathsValues("/instrumentation/encoder/pressure-alt-ft", stod(values.at(8)));
        Maps::setPathsValues("/instrumentation/gps/indicated-altitude-ft", stod(values.at(9)));
        Maps::setPathsValues("/instrumentation/gps/indicated-ground-speed-kt", stod(values.at(10)));
        Maps::setPathsValues("/instrumentation/gps/indicated-vertical-speed", stod(values.at(11)));
        Maps::setPathsValues("/instrumentation/heading-indicator/indicated-heading-deg", stod(values.at(12)));
        Maps::setPathsValues("/instrumentation/magnetic-compass/indicated-heading-deg", stod(values.at(13)));
        Maps::setPathsValues("/instrumentation/slip-skid-ball/indicated-slip-skid", stod(values.at(14)));
        Maps::setPathsValues("/instrumentation/turn-indicator/indicated-turn-rate", stod(values.at(15)));
        Maps::setPathsValues("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", stod(values.at(16)));
        Maps::setPathsValues("/controls/flight/aileron", stod(values.at(17)));
        Maps::setPathsValues("/controls/flight/elevator", stod(values.at(18)));
        Maps::setPathsValues("/controls/flight/rudder", stod(values.at(19)));
        Maps::setPathsValues("/controls/flight/flaps", stod(values.at(20)));
        Maps::setPathsValues("/controls/engines/current-engine/throttle", stod(values.at(21)));
        Maps::setPathsValues("/engines/engine/rpm", stod(values.at(22)));
        map<string, string> mapOfPath = Maps::getMapOfPath();
        for (auto &it : mapOfPath) {
            if (Maps::getSymbolTable().count(it.first)) {
                Maps::setSymbolTable(it.first, Maps::getPathsValues().find(it.second)->second);
            }
        }
    }

    static vector<string> getValues(const string &toSplit, char delimiter) {
        vector<string> result;
        stringstream ss(toSplit);
        string item;
        while (getline(ss, item, delimiter)) {
            result.push_back (item);
        }
        return result;
    }
};