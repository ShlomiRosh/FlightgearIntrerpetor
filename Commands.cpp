#include "Commands.h"
#include <algorithm>
#include <thread>
#include <unistd.h>

void PrintCommand::doCommand(vector<string> parameters, string line) {
    string toPrint;
    for (int i = 1; i < parameters.size(); i++) {
        if (Maps::getSymbolTable().count(parameters[i])) {
            toPrint += parameters[i] + " = ";
            toPrint += to_string(Maps::getSymbolTable().find(parameters[i])->second);
        } else {
            for (int j = 0; j < parameters[i].size(); j++) {
                if (parameters[i][j] != '"') {
                    toPrint += parameters[i][j];
                } else {
                    continue;
                }
            }
        }
        toPrint += " ";
    }
    cout<< toPrint << "\n";
}

void SleepCommand::doCommand(vector<string> parameters, string line) {
    this_thread::sleep_for(chrono::milliseconds(stoi(parameters[1])));
}

void BindCommand::doCommand(vector<string> parameters, string line) {
    string toReplace = parameters[4];
    toReplace.erase(remove(toReplace.begin(), toReplace.end(), '\"'), toReplace.end());
    parameters[4] = toReplace;
    Maps::setMapOfPath(parameters[1], parameters[4]);
    Maps::setSymbolTable(parameters[1], 0);
    Maps::setPathsValues(parameters[4], 0);
}

